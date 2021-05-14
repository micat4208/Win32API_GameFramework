#include "CollisionManager.h"

#include "Framework/Base/GameObject/GameObject.h"

#include "Framework/Base/Component/Collision/RectCollision/RectCollisionComponent.h"
#include "Framework/Base/Component/Collision/CircleCollision/CircleCollisionComponent.h"


bool CCollisionManager::DoCollisionTestCircleToCircle(
	CCollisionComponent* circle1, CCollisionComponent* circle2)
{
	auto circleCollision1 = Cast<CCircleCollisionComponent>(circle1);
	auto circleCollision2 = Cast<CCircleCollisionComponent>(circle2);

	// 두 원의 중심 사이 거리
	float distance = FVector::Distance(
		circleCollision1->GetBounds().GetCenter(), circleCollision2->GetBounds().GetCenter());

	// circleCollision1 의 반지름
	float radius1 = circleCollision1->GetRadius();

	// circleCollision2 의 반지름
	float radius2 = circleCollision2->GetRadius();

	// circleCollision1 과 circleCollision2 가 겹치는 경우 true, 겹치지 않는 경우 false 를 반환하도록 합니다.
	return distance < (radius1 + radius2);
}

bool CCollisionManager::DoCollisionTestRectToRect(CCollisionComponent* rect1, CCollisionComponent* rect2)
{
	auto rectCollision1 = Cast<CRectCollisionComponent>(rect1);
	auto rectCollision2 = Cast<CRectCollisionComponent>(rect2);


	if (rectCollision1->GetBounds().GetLeft() > rectCollision2->GetBounds().GetRight()) return false;
	if (rectCollision1->GetBounds().GetRight() < rectCollision2->GetBounds().GetLeft()) return false;
	if (rectCollision1->GetBounds().GetTop() > rectCollision2->GetBounds().GetBottom()) return false;
	if (rectCollision1->GetBounds().GetBottom() < rectCollision2->GetBounds().GetTop()) return false;

	return true;

	// 두 사각형이 겹쳤을 경우 참을 반환합니다.
	//return
	//	rectCollision1->GetBounds().GetLeft() < rectCollision2->GetBounds().GetRight() &&
	//	rectCollision1->GetBounds().GetRight() > rectCollision2->GetBounds().GetLeft() &&
	//	rectCollision1->GetBounds().GetTop() < rectCollision2->GetBounds().GetBottom() &&
	//	rectCollision1->GetBounds().GetBottom() > rectCollision2->GetBounds().GetTop();

}

bool CCollisionManager::DoCollisionTestRectToCircle(CCollisionComponent* rect, CCollisionComponent* circle)
{
	auto* rectCollision = Cast<CRectCollisionComponent>(rect);
	auto* circleCollision = Cast<CCircleCollisionComponent>(circle);

	// 사각형을 4등분 하여 구한 사각형의 가로 세로 길이
	FVector halfRect = rectCollision->GetBounds().Max - rectCollision->GetBounds().Min;
	// 사각형을 4등분 하여 구한 사각형의 대각선 길이
	float l = sqrt(pow(halfRect.X, 2.0) + pow(halfRect.Y, 2.0f));

	// 사각형과 원의 중심 위치 거리
	float centerDistance = FVector::Distance(
		rectCollision->GetBounds().GetCenter(), 
		circleCollision->GetBounds().GetCenter());

	// 서로 너무 먼 경우 충돌이 일어나지 않음으로 판단
	if ((circleCollision->GetRadius() + l) > centerDistance) return false;

	FVector circleCenter = circleCollision->GetBounds().GetCenter();

	// 원의 중점의 X 좌표가 사각형의 가로 영역 내에 위치하는지,
	// 원의 중점의 Y 좌표가 사각형의 세로 영역 내에 위치하는지 확인합니다.
	if (FMath::IsIn(circleCenter.X, rectCollision->GetBounds().GetLeft(), rectCollision->GetBounds().GetRight()) ||
		FMath::IsIn(circleCenter.Y, rectCollision->GetBounds().GetTop(), rectCollision->GetBounds().GetBottom()))
	{
		// 원의 반지름 길이만큼 확장된 사각 영역을 구합니다.
		FRect expansionRect = rectCollision->GetBounds();
		expansionRect.Min -= FVector::OneVector() * circleCollision->GetRadius();
		expansionRect.Max += FVector::OneVector() * circleCollision->GetRadius();

		// 원의 중심점이 확장된 사각형 내부에 위치하지 않는지 확인합니다.
		if (circleCenter.X < expansionRect.GetLeft()) return false;
		else if (circleCenter.X > expansionRect.GetRight()) return false;
		else if (circleCenter.Y < expansionRect.GetTop()) return false;
		else if (circleCenter.Y > expansionRect.GetBottom()) return false;

		// 아니라면 겹침
		return true;
	}


	// 사각형 가로 세로 크기
	FVector rectCollisionSize = rectCollision->GetBounds().Max - rectCollision->GetBounds().Min;

	// RectCollision 이 사용하는 사각 영역의 네 점의 위치들을 저장합니다.
	FVector rectCollisionPoints[4] =
	{
		// 사각형의 좌측 상단
		rectCollision->GetBounds().Min,
		// 사각형의 좌측 하단
		rectCollision->GetBounds().Min + FVector(0.0f, rectCollisionSize.Y),
		// 사각형의 우측 상단
		rectCollision->GetBounds().Max - FVector(0.0f, rectCollisionSize.Y),
		// 사각형의 우측 하단
		rectCollision->GetBounds().Max
	};

	// 사각형의 네 꼭지점 중 하나라도 원 내에 위치한다면 겹침
	for (FVector point : rectCollisionPoints)
	{
		if (FVector::Distance(circleCenter, point) <= circleCollision->GetRadius()) return true;
	}

	// 아니라면 겹치지 않음
	return false;
}

void CCollisionManager::DoCollisionTest()
{
	if (CreatedCollisions.size() != 0)
	{
		for (auto collision : CreatedCollisions)
			UsedCollisions.push_back(collision);
		CreatedCollisions.clear();
	}

	if (DestroyedCollisions.size() != 0)
	{
		for (auto collision : DestroyedCollisions)
			UsedCollisions.remove(collision);
		DestroyedCollisions.clear();
	}

	// 충돌 검사
	// 사용되는 충돌체가 2개 미만이라면 검사하지 않도록 합니다.
	if (UsedCollisions.size() < 2) return;

	auto iter1 = UsedCollisions.begin();
	auto iter1Fin = --UsedCollisions.end();

	for (; iter1 != iter1Fin; ++iter1)
	{
		auto iter2 = iter1;
		++iter2;

		auto iter2Fin = UsedCollisions.end();

		// 충돌체의 Start() 메서드가 호출되지 않았다면 충돌 검사 X
		if ((*iter1)->bBeDestroy) continue;
		if (!(*iter1)->bIsStarted) continue;

		for (; iter2 != iter2Fin; ++iter2)
		{
			if ((*iter1)->Owner->bBeDestroy || (*iter2)->Owner->bBeDestroy) continue;
			if ((*iter2)->bBeDestroy) continue;
			if (!(*iter2)->bIsStarted) continue;

			using namespace ECollisionType;

			switch ((*iter1)->GetCollisionType())
			{
			case Circle:
				// iter1 과 iter2 가 모두 Circle Collision 일 경우
				if ((*iter2)->GetCollisionType() == Circle)
				{
					// iter1, iter2 가 겹침 상태라면
					if (DoCollisionTestCircleToCircle((*iter1), (*iter2)))
					{
						(*iter1)->OnOverlapped(*iter2);
						(*iter2)->OnOverlapped(*iter1);
					}
				}

				// iter1 이 Circle Collision 이며 iter2 가 Rect Collision 일 경우
				else if ((*iter2)->GetCollisionType() == Circle)
				{
					// iter1, iter2 가 겹침 상태라면
					if (DoCollisionTestRectToCircle((*iter2), (*iter1)))
					{
						(*iter1)->OnOverlapped(*iter2);
						(*iter2)->OnOverlapped(*iter1);
					}
				}
				break;

			case Rect :
				// iter1 과 iter2 가 모두 Rect Collision 일 경우
				if ((*iter2)->GetCollisionType() == Rect)
				{
					// iter1, iter2 가 겹침 상태라면
					if (DoCollisionTestRectToRect((*iter1), (*iter2)))
					{
						(*iter1)->OnOverlapped(*iter2);
						(*iter2)->OnOverlapped(*iter1);
					}
				}

				// iter1 이 Rect Collision 이며 iter2 가 Circle Collision 일 경우
				else if ((*iter2)->GetCollisionType() == Rect)
				{
					// iter1, iter2 가 겹침 상태라면
					if (DoCollisionTestRectToCircle((*iter1), (*iter2)))
					{
						(*iter1)->OnOverlapped(*iter2);
						(*iter2)->OnOverlapped(*iter1);
					}
				}
				break;

			}

		}


	}

}

void CCollisionManager::RegisterCollision(CCollisionComponent* collision)
{
	CreatedCollisions.push_back(collision);
}

void CCollisionManager::UnRegisterCollision(CCollisionComponent* collision)
{
	DestroyedCollisions.push_back(collision);
}

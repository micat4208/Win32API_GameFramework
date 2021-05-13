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

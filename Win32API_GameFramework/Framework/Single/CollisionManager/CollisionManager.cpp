#include "CollisionManager.h"

#include "Framework/Base/GameObject/GameObject.h"

#include "Framework/Base/Component/Collision/RectCollision/RectCollisionComponent.h"
#include "Framework/Base/Component/Collision/CircleCollision/CircleCollisionComponent.h"


bool CCollisionManager::DoCollisionTestCircleToCircle(
	CCollisionComponent* circle1, CCollisionComponent* circle2)
{
	auto circleCollision1 = Cast<CCircleCollisionComponent>(circle1);
	auto circleCollision2 = Cast<CCircleCollisionComponent>(circle2);

	// �� ���� �߽� ���� �Ÿ�
	float distance = FVector::Distance(
		circleCollision1->GetBounds().GetCenter(), circleCollision2->GetBounds().GetCenter());

	// circleCollision1 �� ������
	float radius1 = circleCollision1->GetRadius();

	// circleCollision2 �� ������
	float radius2 = circleCollision2->GetRadius();

	// circleCollision1 �� circleCollision2 �� ��ġ�� ��� true, ��ġ�� �ʴ� ��� false �� ��ȯ�ϵ��� �մϴ�.
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

	// �� �簢���� ������ ��� ���� ��ȯ�մϴ�.
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

	// �簢���� 4��� �Ͽ� ���� �簢���� ���� ���� ����
	FVector halfRect = rectCollision->GetBounds().Max - rectCollision->GetBounds().Min;
	// �簢���� 4��� �Ͽ� ���� �簢���� �밢�� ����
	float l = sqrt(pow(halfRect.X, 2.0) + pow(halfRect.Y, 2.0f));

	// �簢���� ���� �߽� ��ġ �Ÿ�
	float centerDistance = FVector::Distance(
		rectCollision->GetBounds().GetCenter(), 
		circleCollision->GetBounds().GetCenter());

	// ���� �ʹ� �� ��� �浹�� �Ͼ�� �������� �Ǵ�
	if ((circleCollision->GetRadius() + l) > centerDistance) return false;

	FVector circleCenter = circleCollision->GetBounds().GetCenter();

	// ���� ������ X ��ǥ�� �簢���� ���� ���� ���� ��ġ�ϴ���,
	// ���� ������ Y ��ǥ�� �簢���� ���� ���� ���� ��ġ�ϴ��� Ȯ���մϴ�.
	if (FMath::IsIn(circleCenter.X, rectCollision->GetBounds().GetLeft(), rectCollision->GetBounds().GetRight()) ||
		FMath::IsIn(circleCenter.Y, rectCollision->GetBounds().GetTop(), rectCollision->GetBounds().GetBottom()))
	{
		// ���� ������ ���̸�ŭ Ȯ��� �簢 ������ ���մϴ�.
		FRect expansionRect = rectCollision->GetBounds();
		expansionRect.Min -= FVector::OneVector() * circleCollision->GetRadius();
		expansionRect.Max += FVector::OneVector() * circleCollision->GetRadius();

		// ���� �߽����� Ȯ��� �簢�� ���ο� ��ġ���� �ʴ��� Ȯ���մϴ�.
		if (circleCenter.X < expansionRect.GetLeft()) return false;
		else if (circleCenter.X > expansionRect.GetRight()) return false;
		else if (circleCenter.Y < expansionRect.GetTop()) return false;
		else if (circleCenter.Y > expansionRect.GetBottom()) return false;

		// �ƴ϶�� ��ħ
		return true;
	}


	// �簢�� ���� ���� ũ��
	FVector rectCollisionSize = rectCollision->GetBounds().Max - rectCollision->GetBounds().Min;

	// RectCollision �� ����ϴ� �簢 ������ �� ���� ��ġ���� �����մϴ�.
	FVector rectCollisionPoints[4] =
	{
		// �簢���� ���� ���
		rectCollision->GetBounds().Min,
		// �簢���� ���� �ϴ�
		rectCollision->GetBounds().Min + FVector(0.0f, rectCollisionSize.Y),
		// �簢���� ���� ���
		rectCollision->GetBounds().Max - FVector(0.0f, rectCollisionSize.Y),
		// �簢���� ���� �ϴ�
		rectCollision->GetBounds().Max
	};

	// �簢���� �� ������ �� �ϳ��� �� ���� ��ġ�Ѵٸ� ��ħ
	for (FVector point : rectCollisionPoints)
	{
		if (FVector::Distance(circleCenter, point) <= circleCollision->GetRadius()) return true;
	}

	// �ƴ϶�� ��ġ�� ����
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

	// �浹 �˻�
	// ���Ǵ� �浹ü�� 2�� �̸��̶�� �˻����� �ʵ��� �մϴ�.
	if (UsedCollisions.size() < 2) return;

	auto iter1 = UsedCollisions.begin();
	auto iter1Fin = --UsedCollisions.end();

	for (; iter1 != iter1Fin; ++iter1)
	{
		auto iter2 = iter1;
		++iter2;

		auto iter2Fin = UsedCollisions.end();

		// �浹ü�� Start() �޼��尡 ȣ����� �ʾҴٸ� �浹 �˻� X
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
				// iter1 �� iter2 �� ��� Circle Collision �� ���
				if ((*iter2)->GetCollisionType() == Circle)
				{
					// iter1, iter2 �� ��ħ ���¶��
					if (DoCollisionTestCircleToCircle((*iter1), (*iter2)))
					{
						(*iter1)->OnOverlapped(*iter2);
						(*iter2)->OnOverlapped(*iter1);
					}
				}

				// iter1 �� Circle Collision �̸� iter2 �� Rect Collision �� ���
				else if ((*iter2)->GetCollisionType() == Circle)
				{
					// iter1, iter2 �� ��ħ ���¶��
					if (DoCollisionTestRectToCircle((*iter2), (*iter1)))
					{
						(*iter1)->OnOverlapped(*iter2);
						(*iter2)->OnOverlapped(*iter1);
					}
				}
				break;

			case Rect :
				// iter1 �� iter2 �� ��� Rect Collision �� ���
				if ((*iter2)->GetCollisionType() == Rect)
				{
					// iter1, iter2 �� ��ħ ���¶��
					if (DoCollisionTestRectToRect((*iter1), (*iter2)))
					{
						(*iter1)->OnOverlapped(*iter2);
						(*iter2)->OnOverlapped(*iter1);
					}
				}

				// iter1 �� Rect Collision �̸� iter2 �� Circle Collision �� ���
				else if ((*iter2)->GetCollisionType() == Rect)
				{
					// iter1, iter2 �� ��ħ ���¶��
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

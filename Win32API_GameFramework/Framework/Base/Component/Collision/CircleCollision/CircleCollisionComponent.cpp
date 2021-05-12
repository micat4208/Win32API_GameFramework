#include "CircleCollisionComponent.h"
#include "Framework/Base/GameObject/GameObject.h"

CCircleCollisionComponent::CCircleCollisionComponent()
{
	Radius = 0.0f;
	CollisionType = ECollisionType::Circle;
}

void CCircleCollisionComponent::SetRadius(float radius)
{
	Radius = radius;
	FVector center = Owner->Position;
	Bounds = FRect(center, radius * 2.0f, radius * 2.0f);
}

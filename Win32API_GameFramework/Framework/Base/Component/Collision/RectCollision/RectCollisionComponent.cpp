#include "RectCollisionComponent.h"
#include "Framework/Base/GameObject/GameObject.h"

CRectCollisionComponent::CRectCollisionComponent() : 
	CRectCollisionComponent(FVector(0.0f, 0.0f)) { }

CRectCollisionComponent::CRectCollisionComponent(float size) : 
	CRectCollisionComponent(FVector(size, size)) { }

CRectCollisionComponent::CRectCollisionComponent(FVector size)
{
	CollisionType = ECollisionType::Rect;
	Bounds = FRect(Owner->Position, size.X, size.Y);
}

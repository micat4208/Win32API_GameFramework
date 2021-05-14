#include "RectCollisionComponent.h"
#include "Framework/Base/GameObject/GameObject.h"

CRectCollisionComponent::CRectCollisionComponent() : 
	CRectCollisionComponent(FVector(0.0f, 0.0f)) { }

CRectCollisionComponent::CRectCollisionComponent(float size) : 
	CRectCollisionComponent(FVector(size, size)) { }

CRectCollisionComponent::CRectCollisionComponent(FVector size)
{
	Size = size;
	CollisionType = ECollisionType::Rect;
	Bounds = FRect(Owner->Position, Size.X, Size.Y);
}

void CRectCollisionComponent::UpdateBounds()
{
	Bounds = FRect(Owner->Position, Size.X, Size.Y);
}

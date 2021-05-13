#pragma once

#include "Framework/Base/Component/Collision/CollisionComponent.h"

class CRectCollisionComponent :
    public CCollisionComponent
{
public:
    CRectCollisionComponent();
    CRectCollisionComponent(float size);
    CRectCollisionComponent(FVector size);

};
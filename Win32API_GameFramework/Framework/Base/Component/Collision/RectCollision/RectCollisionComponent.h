#pragma once

#include "Framework/Base/Component/Collision/CollisionComponent.h"

class CRectCollisionComponent :
    public CCollisionComponent
{
private :
    FVector Size;

public:
    CRectCollisionComponent();
    CRectCollisionComponent(float size);
    CRectCollisionComponent(FVector size);

protected :
    virtual void UpdateBounds() override;

};
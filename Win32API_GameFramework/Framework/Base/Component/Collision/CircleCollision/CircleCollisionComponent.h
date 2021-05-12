#pragma once
#include "Framework/Base/Component/Collision/CollisionComponent.h"

class CCircleCollisionComponent :
    public CCollisionComponent
{
private :
    float Radius;

public :
    CCircleCollisionComponent();

public :
    void SetRadius(float radius);
    FORCEINLINE float GetRadius() const
    { return Radius; }

};


#pragma once
#include "Framework/Base/Component/Component.h"

// 캐릭터 이동 기능을 제공하는 컴포넌트입니다.
class CMovementComponent :
    public CComponent
{
private :
    // 충격 속도
    FVector Impulse;

    // 이동 가능한 범위 LT
    FVector MovableAreaLT;

    // 이동 가능한 범위 RB
    FVector MovableAreaRB;

public :
    // 최대 속력을 나타냅니다.
    float MaxSpeed;

    // 제동력
    float BrakingForce;

    // 속도
    FVector Velocity;

public :
    CMovementComponent();

public :
    virtual void Tick(float dt) override;

public :
    // 충격 속도를 추가합니다.
    void AddImpulse(FVector impulse);

    // 이동을 추가합니다.
    void AddMovement(FVector direction);

    FORCEINLINE void SetMovableArea(const FVector& lt, const FVector& rb)
    {
        MovableAreaLT = lt;
        MovableAreaRB = rb;
    }

};


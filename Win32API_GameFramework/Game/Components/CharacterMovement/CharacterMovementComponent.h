#pragma once
#include "Framework/Base/Component/Component.h"

// 캐릭터 이동 기능을 제공하는 컴포넌트입니다.
class CCharacterMovementComponent :
    public CComponent
{
private :
    // 이동 방향을 나타냅니다.
    FVector Direction;

    // 최대 속력을 나타냅니다.
    float MaxSpeed;

    // 제동력
    float BrakingForce;

    // 속도
    FVector Velocity;

    // 충격 속도
    FVector Impulse;

public :
    CCharacterMovementComponent();

public :
    virtual void Tick(float dt) override;

public :
    // 충격 속도를 추가합니다.
    void AddImpulse(FVector impulse);

    // 이동을 추가합니다.
    void AddMovement(FVector direction);


public :
    FORCEINLINE float GetMaxSpeed() const
    { return MaxSpeed; }
    FORCEINLINE void SetMaxSpeed(float newMaxSpeed)
    { MaxSpeed = newMaxSpeed; }

    // 속도를 반환합니다.
    FORCEINLINE FVector GetVelocity() const
    { return Velocity; }

    // 속도를 설정합니다.
    FORCEINLINE void SetVelocity(FVector newVelocity)
    { Velocity = newVelocity; } 
};


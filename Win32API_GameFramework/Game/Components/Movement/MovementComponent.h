#pragma once
#include "Framework/Base/Component/Component.h"

// ĳ���� �̵� ����� �����ϴ� ������Ʈ�Դϴ�.
class CMovementComponent :
    public CComponent
{
private :
    // �̵� ������ ��Ÿ���ϴ�.
    FVector Direction;

    // �ִ� �ӷ��� ��Ÿ���ϴ�.
    float MaxSpeed;

    // ������
    float BrakingForce;

    // �ӵ�
    FVector Velocity;

    // ��� �ӵ�
    FVector Impulse;

public :
    CMovementComponent();

public :
    virtual void Tick(float dt) override;

public :
    // ��� �ӵ��� �߰��մϴ�.
    void AddImpulse(FVector impulse);

    // �̵��� �߰��մϴ�.
    void AddMovement(FVector direction);


public :
    FORCEINLINE float GetMaxSpeed() const
    { return MaxSpeed; }
    FORCEINLINE void SetMaxSpeed(float newMaxSpeed)
    { MaxSpeed = newMaxSpeed; }

    // �ӵ��� ��ȯ�մϴ�.
    FORCEINLINE FVector GetVelocity() const
    { return Velocity; }

    // �ӵ��� �����մϴ�.
    FORCEINLINE void SetVelocity(FVector newVelocity)
    { Velocity = newVelocity; } 
};


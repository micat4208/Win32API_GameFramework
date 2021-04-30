#pragma once
#include "Framework/Base/Component/Component.h"

// ĳ���� �̵� ����� �����ϴ� ������Ʈ�Դϴ�.
class CCharacterMovementComponent :
    public CComponent
{
private :
    // �̵� ������ ��Ÿ���ϴ�.
    FVector Direction;

    // �ִ� �ӷ��� ��Ÿ���ϴ�.
    float MaxSpeed;

    // �ӵ�
    FVector Velocity;

public :
    // �ӵ��� ��ȯ�մϴ�.
    FVector GetVelocity() const;

    // �ӵ��� �����մϴ�.
    void SetVelocity(FVector newVelocity);

    // ��� �ӵ��� �߰��մϴ�.
    void AddImpulse(FVector impulse);

    // �̵��� �߰��մϴ�.
    void AddMovement(FVector direction, float deltaSeconds);

public :
    FORCEINLINE float GetMaxSpeed() const
    { return MaxSpeed; }
    FORCEINLINE void SetMaxSpeed(float newMaxSpeed)
    { MaxSpeed = newMaxSpeed; }

};


#pragma once
#include "Framework/Base/Component/Component.h"

// ĳ���� �̵� ����� �����ϴ� ������Ʈ�Դϴ�.
class CMovementComponent :
    public CComponent
{
private :
    // ��� �ӵ�
    FVector Impulse;

    // �̵� ������ ���� LT
    FVector MovableAreaLT;

    // �̵� ������ ���� RB
    FVector MovableAreaRB;

public :
    // �ִ� �ӷ��� ��Ÿ���ϴ�.
    float MaxSpeed;

    // ������
    float BrakingForce;

    // �ӵ�
    FVector Velocity;

public :
    CMovementComponent();

public :
    virtual void Tick(float dt) override;

public :
    // ��� �ӵ��� �߰��մϴ�.
    void AddImpulse(FVector impulse);

    // �̵��� �߰��մϴ�.
    void AddMovement(FVector direction);

    FORCEINLINE void SetMovableArea(const FVector& lt, const FVector& rb)
    {
        MovableAreaLT = lt;
        MovableAreaRB = rb;
    }

};


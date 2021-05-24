#pragma once
#include "Framework/Base/Component/Component.h"
#include "Framework/Enum/Direction.h"

class CPlayerCharacterMovementHelperComponent final :
    public CComponent
{
private :
    class CMovementComponent* Movement;

    // �÷��̾� ĳ���Ͱ� �ٶ󺸴� ������ ��Ÿ���ϴ�.
    EDirection LookDirection;

public :
    CPlayerCharacterMovementHelperComponent();

public :
    virtual void Start() override;
    virtual void Tick(float dt) override;

private :
    // �÷��̾� ĳ���Ͱ� �ٶ󺸴� ������ �����մϴ�.
    void UpdateLookDirection();

public :
    FORCEINLINE EDirection GetLookDirection() const
    { return LookDirection; }



};


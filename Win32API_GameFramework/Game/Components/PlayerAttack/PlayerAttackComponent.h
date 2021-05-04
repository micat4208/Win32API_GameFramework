#pragma once
#include "Framework/Base/Component/Component.h"

class CPlayerAttackComponent final :
    public CComponent
{
private :
    // ���� ������ ��Ÿ���ϴ�.
    FVector AttackDirection;


public :
    virtual void Initialize() override;
    virtual void Tick(float dt) override;

private :
    // �Ѿ��� �߻��մϴ�.
    void FireBullet();


};


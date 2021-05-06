#pragma once
#include "Framework/Base/Component/Component.h"

class CPlayerAttackComponent final :
    public CComponent
{
private :
    class CObjectPool* BulletPool;

    // ���� ������ ��Ÿ���ϴ�.
    FVector AttackDirection;


public :
    virtual void Initialize() override;
    virtual void Tick(float dt) override;
    virtual void Release() override;

private :
    // �Ѿ��� �߻��մϴ�.
    void FireBullet();



};


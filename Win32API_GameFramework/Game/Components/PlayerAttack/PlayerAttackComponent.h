#pragma once
#include "Framework/Base/Component/Component.h"

class CPlayerAttackComponent final :
    public CComponent
{
private :
    class CObjectPool* BulletPool;

    // 공격 방향을 나타냅니다.
    FVector AttackDirection;


public :
    virtual void Initialize() override;
    virtual void Tick(float dt) override;
    virtual void Release() override;

private :
    // 총알을 발사합니다.
    void FireBullet();



};


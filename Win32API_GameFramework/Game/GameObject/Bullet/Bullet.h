#pragma once
#include "Framework/Base/GameObject/GameObject.h"
#include "Framework/Interface/ObjectPoolable.h"

class CBullet final :
    public CGameObject,
    public IObjectPoolable

{
private:
    class CMovementComponent* Movement;
    class CPlayerCharacterRenderer* BulletRenderer;

    // 총알 게임 오브젝트가 생성된 시간을 나타냅니다.
    float CreatedTime;

    // 총알 게임 오브젝트가 씬에서 살아있을 수 있는 시간
    float MaxLifeTime;

    bool bRecyclable;

public:
    virtual void Initialize() override;
    virtual void Tick(float dt) override;

public:
    void InitializeBullet();



    // IObjectPoolable을(를) 통해 상속됨
    FORCEINLINE virtual void SetCanRecyclable(bool bCanRecyclable) override
    { bRecyclable = bCanRecyclable; }


    FORCEINLINE virtual bool GetCanRecyclable() const override
    { return bRecyclable; }

    virtual void OnRecycleStarted() override;

};


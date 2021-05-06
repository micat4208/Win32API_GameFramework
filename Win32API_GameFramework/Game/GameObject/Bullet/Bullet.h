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

    // �Ѿ� ���� ������Ʈ�� ������ �ð��� ��Ÿ���ϴ�.
    float CreatedTime;

    // �Ѿ� ���� ������Ʈ�� ������ ������� �� �ִ� �ð�
    float MaxLifeTime;

    bool bRecyclable;

public:
    virtual void Initialize() override;
    virtual void Tick(float dt) override;

public:
    void InitializeBullet();



    // IObjectPoolable��(��) ���� ��ӵ�
    FORCEINLINE virtual void SetCanRecyclable(bool bCanRecyclable) override
    { bRecyclable = bCanRecyclable; }


    FORCEINLINE virtual bool GetCanRecyclable() const override
    { return bRecyclable; }

    virtual void OnRecycleStarted() override;

};


#pragma once
#include "Framework/Base/GameObject/GameObject.h"

class CBullet final:
    public CGameObject
{
private :
    class CMovementComponent* Movement;

    // �Ѿ� ���� ������Ʈ�� ������ �ð��� ��Ÿ���ϴ�.
    float CreatedTime;

    // �Ѿ� ���� ������Ʈ�� ������ ������� �� �ִ� �ð�
    float MaxLifeTime;

public :
    virtual void Initialize() override;
    virtual void Tick(float dt) override;

public :
    void InitializeBullet();


};


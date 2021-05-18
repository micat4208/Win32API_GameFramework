#pragma once
#include "Framework/Base/GameObject/GameObject.h"

class CCharacter abstract :
    public CGameObject
{
protected :
    class CSpriteRendererComponent* SpriteRenderer;

    // �̵� ����� �����ϴ� ������Ʈ�� ��Ÿ���ϴ�.
    class CMovementComponent* Movement;

private :
    struct FSpriteInfo* TestSpriteInfo;

public :
    virtual void Initialize() override;
    virtual void Tick(float dt) override;
    virtual void Release() override;

};


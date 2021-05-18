#pragma once
#include "Framework/Base/GameObject/GameObject.h"

class CCharacter abstract :
    public CGameObject
{
protected :
    class CSpriteRendererComponent* SpriteRenderer;

    // 이동 기능을 제공하는 컴포넌트를 나타냅니다.
    class CMovementComponent* Movement;

private :
    struct FSpriteInfo* TestSpriteInfo;

public :
    virtual void Initialize() override;
    virtual void Tick(float dt) override;
    virtual void Release() override;

};


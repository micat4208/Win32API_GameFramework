#pragma once
#include "Game/GameObject/Character/Character.h"

class CPlayerCharacter final :
    public CCharacter
{

private :
    class CSpriteAnimationComponent* SpriteAnimation;

public :
    virtual void Initialize() override;
    virtual void Start() override;

    virtual void Tick(float dt) override;
    virtual void Release() override;

private :
    void InputKey(float dt);

};


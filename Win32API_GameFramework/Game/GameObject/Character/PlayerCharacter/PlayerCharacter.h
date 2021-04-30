#pragma once
#include "Game/GameObject/Character/Character.h"

class CPlayerCharacter final :
    public CCharacter
{

public :
    virtual void Initialize() override;
    virtual void Start() override;

    virtual void Tick(float dt) override;

private :
    void InputKey(float dt);

};


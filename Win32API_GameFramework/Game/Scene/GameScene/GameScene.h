#pragma once
#include "Framework/Base/Scene/Scene.h"

class CGameScene final :
    public CScene
{
public :
    virtual void Initialize() override;
    virtual void Tick(float dt) override;
};


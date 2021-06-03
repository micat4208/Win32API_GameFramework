#pragma once
#include "Base/GameObject/GameObject.h"

class CUIObject :
    public CGameObject
{
protected :
    list<class CUIComponent*> UIComponents;

    FVector Size;
    FVector Anchor;

public :
    virtual void Initialize() override;

};


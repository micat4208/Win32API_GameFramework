#pragma once
#include "Base/Component/Scene/Render/RenderComponent.h"

class CUIComponent :
    public CRenderComponent
{
protected :
    // UIObject 를 기준으로 하는 위치
    FVector UIPosition;

    FVector Anchor;

public :
    virtual void Initialize() override;

};


#pragma once
#include "Base/Component/Scene/Render/RenderComponent.h"

class CUIComponent :
    public CRenderComponent
{
protected :
    // UIObject �� �������� �ϴ� ��ġ
    FVector UIPosition;

    FVector Anchor;

public :
    virtual void Initialize() override;

};


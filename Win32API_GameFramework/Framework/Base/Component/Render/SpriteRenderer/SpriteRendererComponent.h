#pragma once
#include "FrameWork/Base/Component/Render/RenderComponent.h"

class CSpriteRendererComponent :
    public CRenderComponent
{

public :
    virtual void Render(HDC hdc) override;

};


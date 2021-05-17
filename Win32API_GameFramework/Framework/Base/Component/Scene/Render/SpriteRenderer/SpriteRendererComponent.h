#pragma once
#include "FrameWork/Base/Component/Scene/Render/RenderComponent.h"
#include "Framework/Struct/SpriteInfo/SpriteInfo.h"

// ��������Ʈ �̹����� �׸��� ������Ʈ
class CSpriteRendererComponent :
    public CRenderComponent
{

private :
    // �׸� ��������Ʈ ����
    FSpriteInfo* DrawSpriteInfo;

public :
    CSpriteRendererComponent();

public :
    virtual void Render(HDC hdc) override;

public :
    FORCEINLINE void SetDrawSpriteInfo(FSpriteInfo* newSpriteInfo)
    { DrawSpriteInfo = newSpriteInfo; }

};


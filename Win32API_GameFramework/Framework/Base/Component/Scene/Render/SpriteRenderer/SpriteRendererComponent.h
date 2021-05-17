#pragma once
#include "FrameWork/Base/Component/Scene/Render/RenderComponent.h"
#include "Framework/Struct/SpriteInfo/SpriteInfo.h"

// 스프라이트 이미지를 그리는 컴포넌트
class CSpriteRendererComponent :
    public CRenderComponent
{

private :
    // 그릴 스프라이트 정보
    FSpriteInfo* DrawSpriteInfo;

public :
    CSpriteRendererComponent();

public :
    virtual void Render(HDC hdc) override;

public :
    FORCEINLINE void SetDrawSpriteInfo(FSpriteInfo* newSpriteInfo)
    { DrawSpriteInfo = newSpriteInfo; }

};


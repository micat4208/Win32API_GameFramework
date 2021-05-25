#pragma once
#include "FrameWork/Base/Component/Scene/Render/RenderComponent.h"
#include "Framework/Struct/SpriteInfo/SpriteInfo.h"

// ��������Ʈ �̹����� �׸��� ������Ʈ
class CSpriteRendererComponent :
    public CRenderComponent
{

protected :
    // �׸� ��������Ʈ ����
    FSpriteInfo* DrawSpriteInfo;

protected :
    bool bIsFlippedX;
    bool bIsFlippedY;

public :
    CSpriteRendererComponent();

public :
    virtual void Render(HDC hdc) override;

    virtual void FlipXY(bool flipX, bool flipY);

public :
    FORCEINLINE void SetDrawSpriteInfo(FSpriteInfo* newSpriteInfo)
    { DrawSpriteInfo = newSpriteInfo; }

    FORCEINLINE void FlipX(bool flipX) { FlipXY(flipX, false); }
    FORCEINLINE void FlipY(bool flipY) { FlipXY(false, flipY); }

    FORCEINLINE bool IsFlippedX() const
    { return bIsFlippedX; }

    FORCEINLINE bool isFlippedY() const
    { return bIsFlippedY; }

};


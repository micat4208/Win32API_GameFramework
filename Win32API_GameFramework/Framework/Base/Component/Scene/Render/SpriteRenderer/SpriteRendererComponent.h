#pragma once
#include "FrameWork/Base/Component/Scene/Render/RenderComponent.h"
#include "Framework/Struct/SpriteInfo/SpriteInfo.h"

// 스프라이트 이미지를 그리는 컴포넌트
CLASS(CSpriteRendererComponent, CRenderComponent)
class CSpriteRendererComponent :
    public CRenderComponent
{
    USE_CLASS(CSpriteRendererComponent);

public :
    // 그릴 스프라이트 정보
    FSpriteInfo* DrawSpriteInfo;

protected :
    bool bIsFlippedX;
    bool bIsFlippedY;

    // 그리기 시작할 좌측 상단 지점
    FVector DrawStartLT;

    // RelativeScale 이 적용된 그려질 스프라이트 이미지 크기
    FVector DrawSpriteImageSize;

public :
    CSpriteRendererComponent();

public :
    virtual void Render(HDC hdc) override;
    virtual void Release() override;

    virtual void FlipXY(bool flipX, bool flipY);

public :
    virtual void SetDrawSpriteInfo(FSpriteInfo* newSpriteInfo);
    

    FORCEINLINE void FlipX(bool flipX) { FlipXY(flipX, false); }
    FORCEINLINE void FlipY(bool flipY) { FlipXY(false, flipY); }

    FORCEINLINE bool IsFlippedX() const
    { return bIsFlippedX; }

    FORCEINLINE bool isFlippedY() const
    { return bIsFlippedY; }

};


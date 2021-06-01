#pragma once
#include "Framework/Base/Component/Scene/Render/SpriteRenderer/SpriteRendererComponent.h"
class CTileMapRendererComponent :
    public CSpriteRendererComponent
{
public:
    // 타일 인덱스
    int32 TileIndexX;
    int32 TileIndexY;
    bool bIsBlockingTile;

private:
    FSpriteInfo* TileMapSpriteInfo;

public:
    virtual void Initialize() override;
    virtual void Render(HDC hdc) override;
    virtual void Release() override;

public:
    // 타일맵 위치를 갱신합니다.
    void UpdatePosition();

    // 그리기 상태를 갱신합니다.
    void UpdateDrawState();
};


#pragma once
#include "Framework/Base/Component/Scene/Render/SpriteRenderer/SpriteRendererComponent.h"

class CTileMapRendererComponent :
    public CSpriteRendererComponent
{
public :
    // 타일 인덱스
    int32 TileIndexX;
    int32 TileIndexY;

private :
    FSpriteInfo* TileMapSpriteInfo;

public :
    virtual void Initialize() override;
    virtual void Release() override;

public :
    // 타일맵 위치를 갱신합니다.
    void UpdatePosition();

};


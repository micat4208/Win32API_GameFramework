#pragma once
#include "Framework/Base/GameObject/GameObject.h"

class CTileMap :
    public CGameObject
{
private :
    int32 TileMapCountX;
    int32 TileMapCountY;
    int32 TileMapScale;

    int32** TileMapData;

    // 추가된 TileMapRenderer 컴포넌트들을 나타냅니다.
    vector<class CTileMapRendererComponent* > TileMapRenderers;



public :
    virtual void Initialize() override;
    virtual void Release() override;

public :
    // 타일맵 XY 크기를 설정합니다.
    void SetTileMapXY(int32 sizeX, int32 sizeY);

    // 타일맵 스케일을 설정합니다.
    void SetTileMapScale(int32 scale);

    // 타일맵을 생성합니다.
    void MakeTileMap();

};


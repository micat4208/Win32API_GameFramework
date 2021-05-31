#pragma once
#include "Framework/Base/GameObject/GameObject.h"

class CTileMap :
    public CGameObject
{
private :
    struct FTileMapInfo* TileMapData;

    int32 TileMapScale;

    // 맵 크기를 나타냅니다.
    /// - 이 값은 RelativeScale 의 영향을 받습니다.
    FVector MapSize;

    // 추가된 TileMapRenderer 컴포넌트들을 나타냅니다.
    vector<class CTileMapRendererComponent* > TileMapRenderers;

    // 타일 그리기 상태를 갱신시키도록 할 것인지에 대한 여부를 나타냅니다.
    bool bUseUpdateTileDrawState;

    // 타일 그리기 상태를 갱신하는 스레드
    FThread* UpdateTileDrawStateThread;



public :
    virtual void Initialize() override;
    virtual void Release() override;

private :
    // 타일맵 정보를 생성합니다.
    void MakeTileMapInfo(string mapCode);

    // 맵 크기를 갱신합니다.
    void UpdateMapSize();

public :
    FORCEINLINE void SetTileMap(string mapCode, int32 tileMapScale = 1)
    { 
        MakeTileMapInfo(mapCode); 
        SetTileMapScale(tileMapScale);
    }

    FORCEINLINE const FVector& GetMapSize() const
    { return MapSize; }

    // 타일맵 XY 크기를 설정합니다.
    void SetTileMapXY(int32 sizeX, int32 sizeY);

    // 타일맵 스케일을 설정합니다.
    void SetTileMapScale(int32 scale);

    // 타일맵을 생성합니다.
    void MakeTileMap();





};


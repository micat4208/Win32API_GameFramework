#pragma once
#include "Framework/Base/GameObject/GameObject.h"

class CTileMap :
    public CGameObject
{
private :
    struct FTileMapInfo* TileMapData;

    int32 TileMapScale;

    // �� ũ�⸦ ��Ÿ���ϴ�.
    /// - �� ���� RelativeScale �� ������ �޽��ϴ�.
    FVector MapSize;

    // �߰��� TileMapRenderer ������Ʈ���� ��Ÿ���ϴ�.
    vector<class CTileMapRendererComponent* > TileMapRenderers;

    // Ÿ�� �׸��� ���¸� ���Ž�Ű���� �� �������� ���� ���θ� ��Ÿ���ϴ�.
    bool bUseUpdateTileDrawState;

    // Ÿ�� �׸��� ���¸� �����ϴ� ������
    FThread* UpdateTileDrawStateThread;



public :
    virtual void Initialize() override;
    virtual void Release() override;

private :
    // Ÿ�ϸ� ������ �����մϴ�.
    void MakeTileMapInfo(string mapCode);

    // �� ũ�⸦ �����մϴ�.
    void UpdateMapSize();

public :
    FORCEINLINE void SetTileMap(string mapCode, int32 tileMapScale = 1)
    { 
        MakeTileMapInfo(mapCode); 
        SetTileMapScale(tileMapScale);
    }

    FORCEINLINE const FVector& GetMapSize() const
    { return MapSize; }

    // Ÿ�ϸ� XY ũ�⸦ �����մϴ�.
    void SetTileMapXY(int32 sizeX, int32 sizeY);

    // Ÿ�ϸ� �������� �����մϴ�.
    void SetTileMapScale(int32 scale);

    // Ÿ�ϸ��� �����մϴ�.
    void MakeTileMap();





};


#pragma once
#include "Framework/Base/GameObject/GameObject.h"

class CTileMap :
    public CGameObject
{
private:
    struct FTileMapInfo* TileMapData;

    int32 TileMapScale;    
    
    // �� ũ�⸦ ��Ÿ��
    // �� ���� RelativeScale�� ������ ����
    FVector MapSize;

    // �߰��� TileMapRenderer ������Ʈ���� ��Ÿ��
    vector<class CTileMapRendererComponent*> TileMapRenderers;

    // Ÿ�� �׸��� ���¸� ���Ž�Ű���� �� �������� ���� ���θ� ��Ÿ��
    bool bUseUpdateTileDrawState;

    // Ÿ�� �׸��� ���¸� �����ϴ� ������
    FThread* UpdateTileDrawStateThread;

public:
    virtual void Initialize() override;
    virtual void Release() override;

private:
    // Ÿ�ϸ� ������ ����
    void MakeTileMapInfo(string mapCode);

    // �� ũ�⸦ ����
    void UpdateMapSize();

public :
    // tileIndexX, tileIndexY �� �ش��ϴ� Ÿ���� ���� ��� ���� �ϴ� ��ġ�� ��ȯ�մϴ�.
    FVector GetTileLT(int32 tileIndexX, int32 tileIndexY);
    FVector GetTileRB(int32 tileIndexX, int32 tileIndexY);

    // tileIndexX, tileIndexY �� �ش��ϴ� Ÿ���� �����ִ� Ÿ������ Ȯ���մϴ�.
    bool IsBlockingTile(int32 tileIndexX, int32 tileIndexY);

public:
    FORCEINLINE void SetTileMap(string mapCode, int32 tileMapScale = 1)
    {
        MakeTileMapInfo(mapCode);
        SetTileMapScale(tileMapScale);
    }

    FORCEINLINE struct FTileMapInfo* GetTileMapData() const
    { return TileMapData; }

    FORCEINLINE const FVector& GetMapSize() const
    {
        return MapSize;
    }

    // Ÿ�ϸ� XY ũ�⸦ ������
    void SetTileMapXY(int32 sizeX, int32 sizeY);

    // Ÿ�ϸ� �������� ����
    void SetTileMapScale(int32 scale);

    // Ÿ�ϸ��� ����
    void MakeTileMap();


};


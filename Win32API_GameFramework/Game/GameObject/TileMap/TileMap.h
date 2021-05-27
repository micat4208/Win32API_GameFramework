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

    // �߰��� TileMapRenderer ������Ʈ���� ��Ÿ���ϴ�.
    vector<class CTileMapRendererComponent* > TileMapRenderers;

    // Ÿ�� �׸��� ���¸� ���Ž�Ű���� �� �������� ���� ���θ� ��Ÿ���ϴ�.
    bool bUseUpdateTileDrawState;

    // Ÿ�� �׸��� ���¸� �����ϴ� ������
    FThread* UpdateTileDrawStateThread;



public :
    virtual void Initialize() override;
    virtual void Release() override;

public :
    // Ÿ�ϸ� XY ũ�⸦ �����մϴ�.
    void SetTileMapXY(int32 sizeX, int32 sizeY);

    // Ÿ�ϸ� �������� �����մϴ�.
    void SetTileMapScale(int32 scale);

    // Ÿ�ϸ��� �����մϴ�.
    void MakeTileMap();

};


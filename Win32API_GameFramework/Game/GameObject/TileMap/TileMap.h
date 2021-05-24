#pragma once
#include "Framework/Base/GameObject/GameObject.h"

class CTileMap :
    public CGameObject
{
private :
    int32 TileMapCountX;
    int32 TileMapCountY;


    int32** TileMapData;



public :
    virtual void Initialize() override;
    virtual void Release() override;

public :
    // Ÿ�ϸ� XY ũ�⸦ �����մϴ�.
    void SetTileMapXY(int32 sizeX, int32 sizeY);

};


#pragma once
#include "Framework/Base/Scene/Scene.h"

class CMapEditorScene final :
    public CScene
{
private :
    int32 TileMapCountX;
    int32 TileMapCountY;

    class CTileMap* TileMap;


public :
    virtual void Initialize() override;
    virtual void Tick(float dt) override;

private :
    static BOOL MapSettingDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);



};


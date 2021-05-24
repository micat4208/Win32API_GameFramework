#include "TileMap.h"

void CTileMap::Initialize()
{
	super::Initialize();

}

void CTileMap::Release()
{
	super::Release();

}

void CTileMap::SetTileMapXY(int32 sizeX, int32 sizeY)
{
	if (sizeX == 0 || sizeY == 0)
	{
		MessageBox(Hwnd, TEXT("�� ũ��� 0 �� �ɼ� �����ϴ�."), TEXT("Error"), MB_OK | MB_ICONSTOP);
		return;
	}

	TileMapCountX = sizeX;
	TileMapCountY = sizeY;
}

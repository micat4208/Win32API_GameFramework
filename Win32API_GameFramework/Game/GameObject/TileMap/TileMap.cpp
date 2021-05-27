#include "TileMap.h"

#include "Game/Components/TileMapRenderer/TileMapRendererComponent.h"

void CTileMap::Initialize()
{
	super::Initialize();

	TileMapData = nullptr;
	TileMapCountX = TileMapCountY = 0;
	TileMapScale = 1;

	bUseUpdateTileDrawState = false;
	UpdateTileDrawStateThread = nullptr;

}

void CTileMap::Release()
{
	// 타일 그리기 상태를 갱신중이라면
	if (UpdateTileDrawStateThread)
	{
		// 타일 그리기 상태 갱신을 중단시킵니다.
		bUseUpdateTileDrawState = false;

		// 스레드 종료를 대기합니다.
		UpdateTileDrawStateThread->join();

		// 해제
		delete UpdateTileDrawStateThread;
		UpdateTileDrawStateThread = nullptr;
	}

	TileMapRenderers.clear();

	if (!TileMapData)
	{
		for (int32 y = 0; y < TileMapCountY; ++y)
			delete[] TileMapData[y];
		delete[] TileMapData;
		TileMapData = nullptr;
	}

	super::Release();

}

void CTileMap::SetTileMapXY(int32 sizeX, int32 sizeY)
{
	if (sizeX == 0 || sizeY == 0)
	{
		MessageBox(Hwnd, TEXT("맵 크기는 0 이 될수 없습니다."), TEXT("Error"), MB_OK | MB_ICONSTOP);
		return;
	}

	TileMapCountX = sizeX;
	TileMapCountY = sizeY;
}

void CTileMap::SetTileMapScale(int32 scale)
{
	if (scale < 1)
	{
		MessageBox(Hwnd, TEXT("타일맵 스케일은 1 미만이 될수 없습니다."), TEXT("Error"), MB_OK | MB_ICONSTOP);
		return;
	}

	TileMapScale = scale;
}

void CTileMap::MakeTileMap()
{
	if (TileMapCountX == 0 || TileMapCountY == 0 || TileMapScale < 1) return;

	TileMapData = new int32 * [TileMapCountY];

	for (int32 y = 0; y < TileMapCountY; ++y)
	{
		TileMapData[y] = new int32[TileMapCountX];
		for (int32 x = 0; x < TileMapCountX; ++x)
		{
			TileMapData[y][x] = 1;
			auto renderer = AddComponent<CTileMapRendererComponent>();

			TileMapRenderers.push_back(renderer);
			renderer->TileIndexX = x;
			renderer->TileIndexY = y;
			renderer->RelativeScale = FVector::OneVector() * (float)TileMapScale;
			renderer->UpdatePosition();
		}
	}

	// 타일 그리기 상태를 계속 갱신시킵니다.
	bUseUpdateTileDrawState = true;
	UpdateTileDrawStateThread = new FThread(
		[this]()
		{
			while (bUseUpdateTileDrawState)
			{
				for (auto tileMapRenderer : TileMapRenderers)
					tileMapRenderer->UpdateDrawState();
			}
		});

}

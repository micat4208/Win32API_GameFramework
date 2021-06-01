#include "TileMap.h"
#include "Game/Components/TileMapRenderer/TileMapRendererComponent.h"
#include "Struct/TileMapInfo/TileMapInfo.h"

void CTileMap::Initialize()
{
	super::Initialize();

	TileMapData = nullptr;
	TileMapScale = 1;

	bUseUpdateTileDrawState = false;
	UpdateTileDrawStateThread = nullptr;
}

void CTileMap::Release()
{
	// Ÿ�� �׸��� ���¸� �������̶��
	if (UpdateTileDrawStateThread)
	{
		// Ÿ�� �׸��� ���� ������ �ߴ�
		bUseUpdateTileDrawState = false;

		// ������ ���Ḧ ��ٸ�
		UpdateTileDrawStateThread->join();

		// ����
		delete UpdateTileDrawStateThread;
		UpdateTileDrawStateThread = nullptr;
	}
	TileMapRenderers.clear();

	if (!TileMapData)
	{
		CObject::DeleteObject(TileMapData);
		TileMapData = nullptr;
	}

	super::Release();
}

void CTileMap::MakeTileMapInfo(string mapCode)
{
	TileMapData = CObject::NewObject<FTileMapInfo>();
	TileMapData->InitializeTileMap(mapCode);

	MakeTileMap();
}

void CTileMap::UpdateMapSize()
{
	if (TileMapRenderers.size() == 0)
		return;

	if (TileMapData->TileMapXCount == 0 || TileMapData->TileMapYCount == 0)
		return;
	auto firstTileMapRenderer = (*TileMapRenderers.begin());
	
	auto tileSpriteInfo = firstTileMapRenderer->DrawSpriteInfo;

	if (tileSpriteInfo == nullptr)
		return;

	if (!tileSpriteInfo->IsValid())
		return;

	MapSize = tileSpriteInfo->SpriteImageSize * TileMapScale;
	MapSize.X *= TileMapData->TileMapXCount;
	MapSize.Y *= TileMapData->TileMapYCount;
}

bool CTileMap::IsBlockingTile(int32 tileIndexX, int32 tileIndexY)
{
	if (TileMapData == nullptr) return false;

	// ���� �� ������ �ƴ� ���� �˻��ϴ� ��� ���� Ÿ�Ϸ� ó���մϴ�.
	if (!FMath::IsIn(tileIndexX, -1, TileMapData->TileMapXCount)) return true;
	if (!FMath::IsIn(tileIndexY, -1, TileMapData->TileMapYCount)) return true;

	return TileMapData->CollisionData[tileIndexY][tileIndexX] == 1;
}

void CTileMap::SetTileMapXY(int32 sizeX, int32 sizeY)
{
	if (sizeX == 0 || sizeY == 0)
	{
		MessageBox(Hwnd, TEXT("�� ũ��� 0�� �� �� �����ϴ�."), TEXT("Error"), MB_OK | MB_ICONSTOP);
		return;
	}

	if (TileMapData == nullptr)
		return;

	TileMapData->TileMapXCount = sizeX;
	TileMapData->TileMapYCount = sizeY;
}

void CTileMap::SetTileMapScale(int32 scale)
{
	if (scale < 1)
	{
		MessageBox(Hwnd, TEXT("Ÿ�ϸ� �������� 1 �̸��� �� �� �����ϴ�."), TEXT("Error"), MB_OK | MB_ICONSTOP);
	}

	TileMapScale = scale;
	
	for (auto renderer : TileMapRenderers)
	{
		renderer->RelativeScale = FVector::OneVector() * (float)TileMapScale;
		renderer->UpdatePosition();
	}

	UpdateMapSize();
}

void CTileMap::MakeTileMap()
{
	if (TileMapData == nullptr)
		return;

	if (TileMapData->TileMapXCount == 0 || TileMapData->TileMapYCount == 0 || TileMapScale < 1)
		return;

	
	for (int32 y = 0; y < TileMapData->TileMapYCount; ++y)
	{
		for (int32 x = 0; x < TileMapData->TileMapXCount; ++x)
		{
			auto renderer = AddComponent<CTileMapRendererComponent>();

			TileMapRenderers.push_back(renderer);
			renderer->TileIndexX = x;
			renderer->TileIndexY = y;
			renderer->bIsBlockingTile = TileMapData->IsBlockingTile(x, y);
			renderer->RelativeScale = FVector::OneVector() * (float)TileMapScale;
			renderer->UpdatePosition();
		}
	}

	UpdateMapSize();

	// Ÿ�� �׸��� ���¸� ��� ���ű�Ŵ
	bUseUpdateTileDrawState = true;
	UpdateTileDrawStateThread = new FThread(
		[this]()
		{
			while (bUseUpdateTileDrawState)
			{
				for (auto tileMapRenderer : TileMapRenderers)
					tileMapRenderer->UpdateDrawState();
			}
		}
	);
}

#include "TileMapRendererComponent.h"

void CTileMapRendererComponent::Initialize()
{
	super::Initialize();

	TileMapSpriteInfo = NewObject<FSpriteInfo>();
	TileMapSpriteInfo->InitializeSpriteInfo(
		TEXT("Resources/DungeonTile/DUNGEON_TILE2.bmp"),
		ESpriteDrawType::UseStretchBlt, USE_LOADED_SIZE, false);

	SetDrawSpriteInfo(TileMapSpriteInfo);
}

void CTileMapRendererComponent::Release()
{
	CObject::DeleteObject(TileMapSpriteInfo);
	super::Release();
}

void CTileMapRendererComponent::UpdatePosition()
{
	if (!DrawSpriteInfo) return;
	if (!DrawSpriteInfo->IsValid()) return;

	FVector tileImageSize = DrawSpriteInfo->SpriteImageSize;

	// ������Ʈ�� Scale �� TileIndexX, Y �� �̿��Ͽ� ������Ʈ�� ��ġ�� �����غ�����!
	RelativePosition = FVector(
		((tileImageSize.X * 0.5) + (TileIndexX * tileImageSize.X)) * RelativeScale.X,
		((tileImageSize.Y * 0.5) + (TileIndexY * tileImageSize.Y)) * RelativeScale.Y);
}

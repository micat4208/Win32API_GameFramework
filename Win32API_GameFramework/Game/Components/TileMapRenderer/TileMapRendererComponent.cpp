#include "TileMapRendererComponent.h"

#include "Framework/Base/Scene/Scene.h"

void CTileMapRendererComponent::Initialize()
{
	super::Initialize();

	TileMapSpriteInfo = NewObject<FSpriteInfo>();
	TileMapSpriteInfo->InitializeSpriteInfo(
		TEXT("Resources/DungeonTile/DUNGEON_TILE2.bmp"),
		ESpriteDrawType::UseStretchBlt, USE_LOADED_SIZE, false);

	DrawSpriteInfo = TileMapSpriteInfo;

	bIsBlockingTile = false;
}

void CTileMapRendererComponent::Render(HDC hdc)
{
	super::Render(hdc);

	if (bIsBlockingTile)
	{
		if (DrawSpriteInfo == nullptr) return;
		if (!DrawSpriteInfo->IsValid()) return;
		if (DrawSpriteInfo->SpriteDrawType == ESpriteDrawType::Hide) return;

		FVector drawSpriteImageSize = FVector(
			DrawSpriteInfo->SpriteImageSize.X * RelativeScale.X,
			DrawSpriteInfo->SpriteImageSize.Y * RelativeScale.Y);

		Rectangle(hdc,
			DrawStartLT.X,
			DrawStartLT.Y,
			DrawStartLT.X + drawSpriteImageSize.X,
			DrawStartLT.Y + drawSpriteImageSize.Y);
	}

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

	RelativePosition = FVector(
		((tileImageSize.X * 0.5) + (TileIndexX * tileImageSize.X)) * RelativeScale.X,
		((tileImageSize.Y * 0.5) + (TileIndexY * tileImageSize.Y)) * RelativeScale.Y);
}

void CTileMapRendererComponent::UpdateDrawState()
{
	auto activeScene = GetActiveScene();
	if (activeScene == nullptr) return;
	if (!bIsStarted) return;
	if (bBeDestroy) return;
	if (!DrawSpriteInfo->IsValid()) return;

	FVector padding = DrawSpriteInfo->SpriteImageSize;
	padding.X *= RelativeScale.X;
	padding.Y *= RelativeScale.Y;
	padding *= 0.5f;

	// 컴포넌트의 위치가 화면 내에 위치할 경우에만 그리도록 합니다.
	bUseRender = GetComponentPosition().InWnd(activeScene->CameraPosition, padding);

}

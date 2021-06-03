#include "PlayerCharacterMovementHelperComponent.h"

#include "GameObject/Character/PlayerCharacter/PlayerCharacter.h"
#include "GameObject/TileMap/TileMap.h"

#include "Components/Movement/MovementComponent.h"

#include "Struct/TileMapInfo/TileMapInfo.h"

CPlayerCharacterMovementHelperComponent::CPlayerCharacterMovementHelperComponent()
{
	Movement = nullptr;
	TileMapIndexX = TileMapIndexY = INDEX_NONE;

	bCheckHorizontalTile = bCheckVerticalTile = false;
}

void CPlayerCharacterMovementHelperComponent::Initialize()
{
	super::Initialize();

	PlayerCharacter = Cast<CPlayerCharacter>(Owner);
}

void CPlayerCharacterMovementHelperComponent::Start()
{
	super::Start();

	// Owner(PlayerCharacter) 에 추가도니 CMovementComponent 컴포넌트를 얻음
	Movement = Owner->GetComponent<CMovementComponent>();

	FVector mapAreaLT = TileMap->Position;
	FVector mapAreaRB = mapAreaLT + TileMap->GetMapSize();	

	Movement->SetMovableArea(mapAreaLT, mapAreaRB);
}

void CPlayerCharacterMovementHelperComponent::Tick(float dt)
{
	super::Tick(dt);	

	bCheckHorizontalTile = FMath::Abs(PlayerCharacter->GetInputAxis().X) > 0.0f;
	bCheckVerticalTile = FMath::Abs(PlayerCharacter->GetInputAxis().Y) > 0.0f;
	
	UpdateLookDirection();

	UpdateTileMapIndex();

	CheckBlockingTile();
}

void CPlayerCharacterMovementHelperComponent::SetTileMap(CTileMap* tileMap)
{
	TileMap = tileMap;
}

void CPlayerCharacterMovementHelperComponent::UpdateLookDirection()
{
	if (Movement == nullptr)
		return;

	// 플레이어 캐릭터의 x 속도를 얻음
	float velocityX = Movement->Velocity.X;

	// 플레이어 캐릭터가 이동중이라면
	if (FMath::Abs(velocityX) > 0.01f)
	{
		// 바라보는 방향 설정
		LookDirection = (FMath::Sign(velocityX) == 1) ? EDirection::Right : EDirection::Left;
	}

	// LOG(TEXT("LookDirection = ") << static_cast<int32>(LookDirection));
}

void CPlayerCharacterMovementHelperComponent::UpdateTileMapIndex()
{
	FTileMapInfo* tileMapInfo = TileMap->GetTileMapData();

	FVector tileMapSize = TileMap->GetMapSize();
	FVector tileSize = FVector(
		tileMapSize.X / tileMapInfo->TileMapXCount,
		tileMapSize.Y / tileMapInfo->TileMapXCount);

	TileMapIndexX = Owner->Position.X / tileSize.X;
	TileMapIndexY = Owner->Position.Y / tileSize.Y;
}

void CPlayerCharacterMovementHelperComponent::CheckBlockingTile()
{
	if (TileMap == nullptr) return;
	if (TileMapIndexX == INDEX_NONE || TileMapIndexY == INDEX_NONE) return;

	// 캐릭터 위치의 타일 바운더리를 얻습니다.
	FRect currentTileBoundaray = FRect(
		TileMap->GetTileLT(TileMapIndexX, TileMapIndexY),
		TileMap->GetTileRB(TileMapIndexX, TileMapIndexY));

	// 맵의 바운더리를 얻습니다.
	FRect mapBoundary = FRect(
		TileMap->Position,
		TileMap->Position + TileMap->GetMapSize());

	// 가로 타일 검사
	Movement->GetMovableAreaLT().X = (TileMap->IsBlockingTile(TileMapIndexX - 1, TileMapIndexY)) ?
		currentTileBoundaray.Min.X : mapBoundary.Min.X;
	Movement->GetMovableAreaRB().X = (TileMap->IsBlockingTile(TileMapIndexX + 1, TileMapIndexY)) ?
		currentTileBoundaray.Max.X : mapBoundary.Max.X;
	
	// 세로 타일 검사
	Movement->GetMovableAreaLT().Y = (TileMap->IsBlockingTile(TileMapIndexX, TileMapIndexY - 1)) ?
		currentTileBoundaray.Min.Y : mapBoundary.Min.Y;
	Movement->GetMovableAreaRB().Y = (TileMap->IsBlockingTile(TileMapIndexX, TileMapIndexY + 1)) ?
		currentTileBoundaray.Max.Y : mapBoundary.Max.Y;


	// 현재 타일 검사
	/// - 현재 타일이 막힌 타일이라면
	if (TileMap->IsBlockingTile(TileMapIndexX, TileMapIndexY))
	{
		int32 tileAxisX = (PlayerCharacter->Position.X < currentTileBoundaray.GetCenter().X) ? -1 : 1;
		int32 tileAxisY = (PlayerCharacter->Position.Y < currentTileBoundaray.GetCenter().Y) ? -1 : 1;

		// 현재 타일의 가장 가까운 경계를 얻습니다.
		FVector nearestBoudary = currentTileBoundaray.GetBoundaryFromIntAxis(tileAxisX, tileAxisY);

		// 플레이어 캐릭터 위치에서 가장 가까운 경계까지의 거리를 구합니다.
		FVector boundaryDistance = FVector(
			FMath::Distance(nearestBoudary.X, PlayerCharacter->Position.X),
			FMath::Distance(nearestBoudary.Y, PlayerCharacter->Position.Y));

		// 최대한 자연스럽게	보이도록 하기 위해, 경계에 가가운 축만 경계로 이동시키며
		// 먼 축은 위치를 옮기지 않습니다.
		if (boundaryDistance.X < boundaryDistance.Y)
			PlayerCharacter->Position.X = nearestBoudary.X;
		else PlayerCharacter->Position.Y = nearestBoudary.Y;
	}
}

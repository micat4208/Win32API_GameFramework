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


	// 검사할 타일 인덱스
	int32 checkingTileIndexX = TileMapIndexX;
	int32 checkingTileIndexY = TileMapIndexY;

	// 변경시킬 축을 가리킬 포인터
	float* targetAxis = nullptr;

	// 캐릭터 위치의 타일 바운더리를 얻습니다.
	FRect currentTileBoundaray = FRect(
		TileMap->GetTileLT(TileMapIndexX, TileMapIndexY),
		TileMap->GetTileRB(TileMapIndexX, TileMapIndexY));

	// 맵의 바운더리를 얻습니다.
	FRect mapBoundary = FRect(
		TileMap->Position,
		TileMap->Position + TileMap->GetMapSize());



	// 가로 타일 검사
	if (bCheckHorizontalTile)
	{
		// 검사할 타일 방향을 저장합니다.
		/// - 좌측으로 이동중이라면 좌측 타일을, 우측으로 이동중이라면 우측 타일을 검사하도록 합니다.
		EDirection checkingTileDirection = (PlayerCharacter->GetInputAxis().X < 0.0f) ? 
			EDirection::Left : EDirection::Right;

		// 검사시킬 타일 인덱스를 설정합니다.
		checkingTileIndexX += (checkingTileDirection == EDirection::Left) ? -1 : 1;

		// 변경시킬 축을 저장합니다.
		targetAxis = (checkingTileDirection == EDirection::Left) ?
			&Movement->GetMovableAreaLT().X :
			&Movement->GetMovableAreaRB().X;

		// 이동 제한에 사용될 바운더리를 얻습니다.
		/// - 만약 TileMapIndexX, TileMapIndexY 에 해당하는 타일이 막힌 타일이라면
		///   현재 캐릭터가 위치한 타일의 바운더리를 사용, 막힌 타일이 아니라면 맵의 바운더리를 사용하도록 합니다.
		FRect& boundary = (TileMap->IsBlockingTile(checkingTileIndexX, checkingTileIndexY)) ?
			currentTileBoundaray : mapBoundary;

		// 캐릭터가 이동 가능한 위치를 설정합니다.
		*targetAxis = (checkingTileDirection == EDirection::Left) ?
			boundary.GetLeft() : boundary.GetRight();
	}

	checkingTileIndexX = TileMapIndexX;

	// 세로 타일 검사
	if (bCheckVerticalTile)
	{

		// 검사할 타일 방향을 저장합니다.
		/// - 상단으로 이동중이라면 상단 타일을, 하단으로 이동중이라면 하단 타일을 검사하도록 합니다.
		EDirection checkingTileDirection = (PlayerCharacter->GetInputAxis().Y < 0.0f) ?
			EDirection::Up : EDirection::Down;

		// 검사시킬 타일 인덱스를 설정합니다.
		checkingTileIndexY += (checkingTileDirection == EDirection::Up) ? -1 : 1;

		// 변경시킬 축을 저장합니다.
		targetAxis = (checkingTileDirection == EDirection::Up) ?
			&Movement->GetMovableAreaLT().Y :
			&Movement->GetMovableAreaRB().Y;

		// 이동 제한에 사용될 바운더리를 얻습니다.
		/// - 만약 TileMapIndexX, TileMapIndexY 에 해당하는 타일이 막힌 타일이라면
		///   현재 캐릭터가 위치한 타일의 바운더리를 사용, 막힌 타일이 아니라면 맵의 바운더리를 사용하도록 합니다.
		FRect& boundary = (TileMap->IsBlockingTile(checkingTileIndexX, checkingTileIndexY)) ?
			currentTileBoundaray : mapBoundary;

		// 캐릭터가 이동 가능한 위치를 설정합니다.
		*targetAxis = (checkingTileDirection == EDirection::Up) ?
			boundary.GetTop() : boundary.GetBottom();
	}

	// 현재 타일 검사
	if (TileMap->IsBlockingTile(TileMapIndexX, TileMapIndexY))
	{

		// 현재 타일의 중심 위치를 얻습니다.
		FVector currentTileCenter = currentTileBoundaray.GetCenter();

		FVector newPosition(
			(Owner->Position.X < currentTileCenter.X) ?
			currentTileBoundaray.GetLeft() - 0.001f : currentTileBoundaray.GetRight() + 0.001f,
			(Owner->Position.Y < currentTileCenter.Y) ?
			currentTileBoundaray.GetTop() - 0.001f : currentTileBoundaray.GetBottom() + 0.001f);

		Owner->Position = newPosition;
	}

}

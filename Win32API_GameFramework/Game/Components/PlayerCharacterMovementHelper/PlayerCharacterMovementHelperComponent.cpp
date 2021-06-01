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

	bCheckHorizontalTile = (FMath::Abs(PlayerCharacter->GetInputAxis().X) > 0.01f);
	bCheckVerticalTile = (FMath::Abs(PlayerCharacter->GetInputAxis().Y) > 0.01f);
	
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

		LOG(TEXT("block ? = ") << TileMap->IsBlockingTile(checkingTileIndexX, checkingTileIndexY));

		//*targetAxis = 


		

	}

	// 세로 타일 검사
	if (bCheckVerticalTile)
	{

	}

}

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

	// Owner(PlayerCharacter) �� �߰����� CMovementComponent ������Ʈ�� ����
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

	// �÷��̾� ĳ������ x �ӵ��� ����
	float velocityX = Movement->Velocity.X;

	// �÷��̾� ĳ���Ͱ� �̵����̶��
	if (FMath::Abs(velocityX) > 0.01f)
	{
		// �ٶ󺸴� ���� ����
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


	// �˻��� Ÿ�� �ε���
	int32 checkingTileIndexX = TileMapIndexX;
	int32 checkingTileIndexY = TileMapIndexY;

	// �����ų ���� ����ų ������
	float* targetAxis = nullptr;

	// ���� Ÿ�� �˻�
	if (bCheckHorizontalTile)
	{
		// �˻��� Ÿ�� ������ �����մϴ�.
		/// - �������� �̵����̶�� ���� Ÿ����, �������� �̵����̶�� ���� Ÿ���� �˻��ϵ��� �մϴ�.
		EDirection checkingTileDirection = (PlayerCharacter->GetInputAxis().X < 0.0f) ? 
			EDirection::Left : EDirection::Right;

		// �˻��ų Ÿ�� �ε����� �����մϴ�.
		checkingTileIndexX += (checkingTileDirection == EDirection::Left) ? -1 : 1;

		// �����ų ���� �����մϴ�.
		targetAxis = (checkingTileDirection == EDirection::Left) ?
			&Movement->GetMovableAreaLT().X :
			&Movement->GetMovableAreaRB().X;

		LOG(TEXT("block ? = ") << TileMap->IsBlockingTile(checkingTileIndexX, checkingTileIndexY));

		//*targetAxis = 


		

	}

	// ���� Ÿ�� �˻�
	if (bCheckVerticalTile)
	{

	}

}

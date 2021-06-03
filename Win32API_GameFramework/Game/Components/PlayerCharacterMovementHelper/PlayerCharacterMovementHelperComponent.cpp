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

	// ĳ���� ��ġ�� Ÿ�� �ٿ������ ����ϴ�.
	FRect currentTileBoundaray = FRect(
		TileMap->GetTileLT(TileMapIndexX, TileMapIndexY),
		TileMap->GetTileRB(TileMapIndexX, TileMapIndexY));

	// ���� �ٿ������ ����ϴ�.
	FRect mapBoundary = FRect(
		TileMap->Position,
		TileMap->Position + TileMap->GetMapSize());

	// ���� Ÿ�� �˻�
	Movement->GetMovableAreaLT().X = (TileMap->IsBlockingTile(TileMapIndexX - 1, TileMapIndexY)) ?
		currentTileBoundaray.Min.X : mapBoundary.Min.X;
	Movement->GetMovableAreaRB().X = (TileMap->IsBlockingTile(TileMapIndexX + 1, TileMapIndexY)) ?
		currentTileBoundaray.Max.X : mapBoundary.Max.X;
	
	// ���� Ÿ�� �˻�
	Movement->GetMovableAreaLT().Y = (TileMap->IsBlockingTile(TileMapIndexX, TileMapIndexY - 1)) ?
		currentTileBoundaray.Min.Y : mapBoundary.Min.Y;
	Movement->GetMovableAreaRB().Y = (TileMap->IsBlockingTile(TileMapIndexX, TileMapIndexY + 1)) ?
		currentTileBoundaray.Max.Y : mapBoundary.Max.Y;


	// ���� Ÿ�� �˻�
	/// - ���� Ÿ���� ���� Ÿ���̶��
	if (TileMap->IsBlockingTile(TileMapIndexX, TileMapIndexY))
	{
		int32 tileAxisX = (PlayerCharacter->Position.X < currentTileBoundaray.GetCenter().X) ? -1 : 1;
		int32 tileAxisY = (PlayerCharacter->Position.Y < currentTileBoundaray.GetCenter().Y) ? -1 : 1;

		// ���� Ÿ���� ���� ����� ��踦 ����ϴ�.
		FVector nearestBoudary = currentTileBoundaray.GetBoundaryFromIntAxis(tileAxisX, tileAxisY);

		// �÷��̾� ĳ���� ��ġ���� ���� ����� �������� �Ÿ��� ���մϴ�.
		FVector boundaryDistance = FVector(
			FMath::Distance(nearestBoudary.X, PlayerCharacter->Position.X),
			FMath::Distance(nearestBoudary.Y, PlayerCharacter->Position.Y));

		// �ִ��� �ڿ�������	���̵��� �ϱ� ����, ��迡 ������ �ุ ���� �̵���Ű��
		// �� ���� ��ġ�� �ű��� �ʽ��ϴ�.
		if (boundaryDistance.X < boundaryDistance.Y)
			PlayerCharacter->Position.X = nearestBoudary.X;
		else PlayerCharacter->Position.Y = nearestBoudary.Y;
	}
}

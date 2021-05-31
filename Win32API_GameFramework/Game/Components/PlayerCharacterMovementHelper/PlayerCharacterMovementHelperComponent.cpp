#include "PlayerCharacterMovementHelperComponent.h"

#include "Framework/Base/GameObject/GameObject.h"
#include "Game/GameObject/TileMap/TileMap.h"
#include "Game/Components/Movement/MovementComponent.h"

CPlayerCharacterMovementHelperComponent::CPlayerCharacterMovementHelperComponent()
{
	Movement = nullptr;
}

void CPlayerCharacterMovementHelperComponent::Start()
{
	super::Start();

	// Owner(PlayerCharacter) �� �߰��� CMovementComponent ������Ʈ�� ����ϴ�.
	Movement = Owner->GetComponent<CMovementComponent>();

	FVector mapAreaLT = TileMap->Position;
	FVector mapAreaRB = mapAreaLT + TileMap->GetMapSize();

	Movement->SetMovableArea(mapAreaLT, mapAreaRB);
}

void CPlayerCharacterMovementHelperComponent::Tick(float dt)
{
	super::Tick(dt);

	UpdateLookDirection();
}

void CPlayerCharacterMovementHelperComponent::SetTileMap(CTileMap* tileMap)
{
	TileMap = tileMap;
}

void CPlayerCharacterMovementHelperComponent::UpdateLookDirection()
{
	if (Movement == nullptr) return;

	// �÷��̾� ĳ���� X �ӵ��� ����ϴ�.
	float velocityX = Movement->Velocity.X;

	// �÷��̾� ĳ���Ͱ� �̵����̶��
	if (FMath::Abs(velocityX) > 0.01f)
		// �ٶ󺸴� ������ �����մϴ�.
		LookDirection = (FMath::Sign(velocityX) == 1) ? EDirection::Right : EDirection::Left;
}

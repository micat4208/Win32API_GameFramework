#include "PlayerCharacter.h"

#include "Framework/Single/InputManager/InputManager.h"

#include "Game/Components/Movement/MovementComponent.h"
#include "Game/GameObject/TileMap/TileMap.h"

#include "Game/Components/PlayerSpriteAnimation/PlayerSpriteAnimationComponent.h"
#include "Game/Components/PlayerCharacterMovementHelper/PlayerCharacterMovementHelperComponent.h"

#include "Game/Scene/GameScene/GameScene.h"

void CPlayerCharacter::Initialize()
{
	super::Initialize();
	Position = FVector::ScreenCenter();
	Movement->MaxSpeed = 300.0f;
	Movement->BrakingForce = 1000.0f;

	SpriteAnimation = AddComponent<CPlayerSpriteAnimationComponent>();
	MovementHelper = AddComponent<CPlayerCharacterMovementHelperComponent>();

	// 타일 맵 설정
	MovementHelper->SetTileMap(Cast<CGameScene>(OwnerScene)->GetTileMap());
}

void CPlayerCharacter::Start()
{
	super::Start();
}

void CPlayerCharacter::Tick(float dt)
{
	super::Tick(dt);

	InputKey(dt);
}

void CPlayerCharacter::Release()
{
	super::Release();
}

void CPlayerCharacter::InputKey(float dt)
{
	// 키 입력값을 저장합니다.
	InputAxis = FVector(
		CInput::GetAxis(TEXT("Horizontal")),
		CInput::GetAxis(TEXT("Vertical")));

	Movement->AddMovement(FVector::RightVector() * InputAxis.X);
	
	Movement->AddMovement(FVector::DownVector() * InputAxis.Y);

	if (CInput::GetKeyDown(TEXT("Space")))
	{
		Movement->AddImpulse(FVector::RightVector() * 1000.0f);
	}
}

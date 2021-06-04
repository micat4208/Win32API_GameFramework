#include "PlayerCharacter.h"

#include "Single/InputManager/InputManager.h"

#include "Components/Movement/MovementComponent.h"
#include "GameObject/TileMap/TileMap.h"

#include "Components/PlayerSpriteAnimation/PlayerSpriteAnimationComponent.h"
#include "Components/PlayerCharacterMovementHelper/PlayerCharacterMovementHelperComponent.h"

#include "Base/GameObject/ScreenObject/ScreenObject.h"
#include "GameObject/UIObject/PlayerUI/PlayerUI.h"

#include "Base/GameObject/UIObject/UIObject.h"

#include "Scene/GameScene/GameScene.h"

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

	OwnerScene->GetScreen()->CreateUIObject<CUIObject>();
}

void CPlayerCharacter::Start()
{
	super::Start();

	FloatingPlayerUI();
}

void CPlayerCharacter::Tick(float dt)
{
	super::Tick(dt);

	InputKey(dt);

	// 카메라 이동
	OwnerScene->CameraPosition = FVector::Lerp(
		OwnerScene->CameraPosition, Position, 3.0f * dt);
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

void CPlayerCharacter::FloatingPlayerUI()
{
	OwnerScene->GetScreen()->CreateUIObject<CPlayerUI>();
}

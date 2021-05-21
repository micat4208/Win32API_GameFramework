#include "PlayerCharacter.h"

#include "Framework/Single/InputManager/InputManager.h"

#include "Game/Components/Movement/MovementComponent.h"

#include "Game/Components/PlayerSpriteAnimation/PlayerSpriteAnimationComponent.h"

void CPlayerCharacter::Initialize()
{
	super::Initialize();
	Position = FVector::ScreenCenter();
	Movement->MaxSpeed = 300.0f;
	Movement->BrakingForce = 1000.0f;

	SpriteAnimation = AddComponent<CPlayerSpriteAnimationComponent>();
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
	Movement->AddMovement(FVector::DownVector() * CInput::GetAxis(TEXT("Vertical")));
	Movement->AddMovement(FVector::RightVector() * CInput::GetAxis(TEXT("Horizontal")));

	if (CInput::GetKeyDown(TEXT("Space")))
	{
		Movement->AddImpulse(FVector::RightVector() * 1000.0f);
	}
}

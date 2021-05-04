#include "PlayerCharacter.h"

#include "Framework/Single/InputManager/InputManager.h"

#include "Game/Components/PlayerCharacterRenderer/PlayerCharacterRenderer.h"
#include "Game/Components/Movement/MovementComponent.h"
#include "Game/Components/PlayerAttack/PlayerAttackComponent.h"

void CPlayerCharacter::Initialize()
{
	super::Initialize();

	AddComponent<CPlayerCharacterRenderer>();
	AddComponent<CPlayerAttackComponent>();

	Position = FVector::ScreenCenter();
	Movement->SetMaxSpeed(300.0f);
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

void CPlayerCharacter::InputKey(float dt)
{
	Movement->AddMovement(
		FVector::DownVector() * CInput::GetAxis(TEXT("Vertical")));

	Movement->AddMovement(
		FVector::RightVector() * CInput::GetAxis(TEXT("Horizontal")));

	if (CInput::GetKeyDown(TEXT("Space")))
	{
		Movement->AddImpulse(FVector::RightVector() * 1000.0f);
	}
}

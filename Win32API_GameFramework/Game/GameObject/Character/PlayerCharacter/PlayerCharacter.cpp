#include "PlayerCharacter.h"

#include "Framework/Single/InputManager/InputManager.h"

#include "Game/Components/PlayerCharacterRenderer/PlayerCharacterRenderer.h"
#include "Game/Components/CharacterMovement/CharacterMovementComponent.h"

void CPlayerCharacter::Initialize()
{
	super::Initialize();

	AddComponent<CPlayerCharacterRenderer>();

	Position = FVector::ScreenCenter();
	CharacterMovement->SetMaxSpeed(300.0f);
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
	CharacterMovement->AddMovement(
		FVector::DownVector() * CInput::GetAxis(TEXT("Vertical")));

	CharacterMovement->AddMovement(
		FVector::RightVector() * CInput::GetAxis(TEXT("Horizontal")));

}

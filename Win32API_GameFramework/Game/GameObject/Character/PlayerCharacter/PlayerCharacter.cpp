#include "PlayerCharacter.h"

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
	float axisValue = 0.0f;
	if (GetAsyncKeyState(VK_LEFT))
		axisValue -= 1.0f;
	else if (GetAsyncKeyState(VK_RIGHT))
		axisValue += 1.0f;

	CharacterMovement->AddMovement(FVector::RightVector() * axisValue, dt);
}

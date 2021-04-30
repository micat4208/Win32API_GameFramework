#include "Character.h"

#include "Game/Components/CharacterMovement/CharacterMovementComponent.h"

void CCharacter::Initialize()
{
	super::Initialize();

	CharacterMovement = AddComponent<CCharacterMovementComponent>();
}

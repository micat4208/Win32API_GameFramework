#include "Character.h"

#include "Game/Components/Movement/MovementComponent.h"

void CCharacter::Initialize()
{
	super::Initialize();

	Movement = AddComponent<CMovementComponent>();
}

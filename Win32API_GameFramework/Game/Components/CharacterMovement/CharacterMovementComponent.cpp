#include "CharacterMovementComponent.h"

FVector CCharacterMovementComponent::GetVelocity() const
{
    return FVector();
}

void CCharacterMovementComponent::SetVelocity(FVector newVelocity)
{
}

void CCharacterMovementComponent::AddImpulse(FVector impulse)
{
}

void CCharacterMovementComponent::AddMovement(FVector direction, float deltaSeconds)
{
    Velocity = direction.Normalized() * MaxSpeed * deltaSeconds;

}

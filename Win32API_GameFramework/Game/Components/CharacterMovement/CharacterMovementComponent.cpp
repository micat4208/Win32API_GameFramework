#include "CharacterMovementComponent.h"
#include "Framework/Base/GameObject/GameObject.h"


CCharacterMovementComponent::CCharacterMovementComponent()
{
    Impulse = Velocity = Direction = FVector::ZeroVector();
    MaxSpeed = 600.0f;
    BrakingForce = 100.0f; // %
}

void CCharacterMovementComponent::Tick(float dt)
{
    super::Tick(dt);
    Owner->Position += (Velocity + Impulse) * dt;

    Velocity = FVector(
        FMath::Lerp(Velocity.X, 0.0f, dt * ((MaxSpeed * 0.01f) * BrakingForce * dt)),
        FMath::Lerp(Velocity.Y, 0.0f, dt * ((MaxSpeed * 0.01f) * BrakingForce * dt)));

    Impulse = FVector(
        FMath::Lerp(Impulse.X, 0.0f, dt * ((MaxSpeed * 0.01f) * BrakingForce * dt)),
        FMath::Lerp(Impulse.Y, 0.0f, dt * ((MaxSpeed * 0.01f) * BrakingForce * dt)));
}

void CCharacterMovementComponent::AddImpulse(FVector impulse)
{
    Impulse = impulse;
}

void CCharacterMovementComponent::AddMovement(FVector direction)
{
    Velocity += direction.Normalized() * MaxSpeed;

    if (Velocity.Length() > MaxSpeed)
    {
        Velocity.Normalize();
        Velocity *= MaxSpeed;
    }

}

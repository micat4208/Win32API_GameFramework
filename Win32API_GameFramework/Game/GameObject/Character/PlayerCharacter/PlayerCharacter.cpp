#include "PlayerCharacter.h"

#include "Framework/Single/InputManager/InputManager.h"

#include "Game/Components/Movement/MovementComponent.h"

#include "Framework/Base/Component/Scene/Render/SpriteRenderer/SpriteRendererComponent.h"

void CPlayerCharacter::Initialize()
{
	super::Initialize();
	Position = FVector::ScreenCenter();
	Movement->SetMaxSpeed(300.0f);

	SpriteRenderer = AddComponent<CSpriteRendererComponent>();
	TestSpriteInfo = CObject::NewObject<FSpriteInfo>();
	TestSpriteInfo->InitializeSpriteInfo(
		TEXT("Resources/PlayerCharacter/IDLE/IDLE 1.bmp"), 
		ESpriteDrawType::UseTransparentBlt);
	SpriteRenderer->SetDrawSpriteInfo(TestSpriteInfo);
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
	CObject::DeleteObject(TestSpriteInfo);

	super::Release();
}

void CPlayerCharacter::InputKey(float dt)
{
	Movement->AddMovement(
		FVector::DownVector() * CInput::GetAxis(TEXT("Vertical")));

	float horizontalInput = CInput::GetAxis(TEXT("Horizontal"));
	Movement->AddMovement(FVector::RightVector() * horizontalInput);

	SpriteRenderer->FlipX(horizontalInput < -0.1);

	if (CInput::GetKeyDown(TEXT("Space")))
	{
		Movement->AddImpulse(FVector::RightVector() * 1000.0f);
	}
}

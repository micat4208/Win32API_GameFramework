#include "Character.h"

#include "Framework/Single/InputManager/InputManager.h"
#include "Framework/Bitmap/Bitmap.h"

#include "Framework/Base/Component/Scene/Render/SpriteRenderer/SpriteRendererComponent.h"

#include "Game/Components/Movement/MovementComponent.h"

void CCharacter::Initialize()
{
	super::Initialize();

	SpriteRenderer = AddComponent<CSpriteRendererComponent>();
	Movement = AddComponent<CMovementComponent>();

	// SpriteRenderer Test Code
	{
		TestSpriteInfo = CObject::NewObject<FSpriteInfo>();
		TestSpriteInfo->InitializeSpriteInfo(
			TEXT("Resources/PlayerCharacter/WALK 1.bmp"),
			ESpriteDrawType::UseTransparentBlt);
		TestSpriteInfo->CRTransparent = RGB(255, 0, 255);

		SpriteRenderer->SetDrawSpriteInfo(TestSpriteInfo);
		SpriteRenderer->RelativeScale = FVector::OneVector() * 0.3f;
	}
}

void CCharacter::Tick(float dt)
{
	super::Tick(dt);

	if (CInput::GetKeyDown(TEXT("FireBullet")))
		TestSpriteInfo->GetLoadedBitmap()->FlipXY(true, false);

}

void CCharacter::Release()
{
	CObject::DeleteObject(TestSpriteInfo);

	super::Release();
}

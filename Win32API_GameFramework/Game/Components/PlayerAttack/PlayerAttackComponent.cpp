#include "PlayerAttackComponent.h"

#include "Framework/Single/InputManager/InputManager.h"
#include "Framework/Statics/GameplayStatics.h"
#include "Framework/Base/Scene/Scene.h"

#include "Game/GameObject/Bullet/Bullet.h"



void CPlayerAttackComponent::Initialize()
{
	super::Initialize();

	AttackDirection = FVector::ZeroVector();
}

void CPlayerAttackComponent::Tick(float dt)
{
	super::Tick(dt);

	if (CInput::GetKey(TEXT("FireBullet")))
		FireBullet();

	FVector cursorPos = CGameplayStatics::GetMousePosition();
	LOG(TEXT("CursorXY In Client = ") << cursorPos.ToString());
}

void CPlayerAttackComponent::FireBullet()
{
	static int bulletCount = 0;
	for (int32 i = 0; i < 50; ++i)
	{
		++bulletCount;

		CBullet* newBullet = Owner->OwnerScene->NewGameObject<CBullet>();
		newBullet->InitializeBullet();
		newBullet->Position = Owner->Position;


		LOG(TEXT("bulletCount = ") << bulletCount);
	}

}

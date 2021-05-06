#include "Bullet.h"
#include "Framework/Statics/GameplayStatics.h"
#include "Framework/Base/Scene/Scene.h"

#include "Game/Components/Movement/MovementComponent.h"
#include "Game/Components/PlayerCharacterRenderer/PlayerCharacterRenderer.h"

void CBullet::Initialize()
{
	super::Initialize();
	BulletRenderer = AddComponent<CPlayerCharacterRenderer>();
	Movement = AddComponent<CMovementComponent>();
	MaxLifeTime = 3.0f;
	bRecyclable = false;
}

void CBullet::Tick(float dt)
{
	super::Tick(dt);

	if (CGameplayStatics::GetTime() - CreatedTime >= MaxLifeTime)
	{
		BulletRenderer->bUseRender = false;
		bRecyclable = true;
	}
		//OwnerScene->Destroy(this);
}

void CBullet::InitializeBullet()
{
	CreatedTime = CGameplayStatics::GetTime();

	BulletRenderer->bUseRender = true;
}

void CBullet::OnRecycleStarted()
{
}

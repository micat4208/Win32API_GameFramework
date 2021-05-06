#include "PlayerAttackComponent.h"

#include "Framework/Single/InputManager/InputManager.h"
#include "Framework/Statics/GameplayStatics.h"
#include "Framework/Base/Scene/Scene.h"

#include "Framework/Util/ObjectPool.h"

#include "Game/GameObject/Bullet/Bullet.h"

void CPlayerAttackComponent::Initialize()
{
	super::Initialize();

	BulletPool = CObject::NewObject<CObjectPool>();
	AttackDirection = FVector::ZeroVector();
}

void CPlayerAttackComponent::Tick(float dt)
{
	super::Tick(dt);

	if (CInput::GetKey(TEXT("FireBullet")))
		FireBullet();

	FVector cursorPos = CGameplayStatics::GetMousePosition();
}

void CPlayerAttackComponent::Release()
{
	super::Release();

	CObject::DeleteObject(BulletPool);
}

void CPlayerAttackComponent::FireBullet()
{

	CBullet* newBullet = BulletPool->GetRecycledObject<CBullet>();
	newBullet = (newBullet != nullptr) ?
		newBullet :
		BulletPool->RegisterRecyclableObject(Owner->OwnerScene->NewGameObject<CBullet>());

	newBullet->InitializeBullet();
	newBullet->Position = Owner->Position;
}

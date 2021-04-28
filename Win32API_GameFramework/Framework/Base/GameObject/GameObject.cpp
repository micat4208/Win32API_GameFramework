#include "GameObject.h"

#include "Framework/Base/Scene/Scene.h"

CGameObject::CGameObject()
{
	OwnerScene = nullptr;

	bCanEverTick = true;
	bIsStarted = bBeDestroy = false;
}

void CGameObject::Initialize()
{
	super::Initialize();
}

void CGameObject::Start()
{
	bIsStarted = true;
}

void CGameObject::Tick(float DeltaSeconds)
{
}

void CGameObject::OnDestroy()
{
}

void CGameObject::Release()
{
	super::Release();
}

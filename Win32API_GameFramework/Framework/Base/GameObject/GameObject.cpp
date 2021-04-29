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
	// 생성된 컴포넌트가 존재한다면
	if (CreatedComponents.size() > 0)
	{
		// 사용되는 컴포넌트 리스트에 추가합니다.
		for (auto createdComponent : CreatedComponents)
			UsedComponents.push_back(createdComponent);
		CreatedComponents.clear();
	}

	// 제거된 컴포넌트가 존재한다면
	if (DestroyedComponents.size() > 0)
	{
		for (auto destroyedComponent : DestroyedComponents)
		{
			// 해제시킬 컴포넌트를 사용중인 컴포넌트들에서 제외합니다.
			UsedComponents.remove(destroyedComponent);

			// 메모리 해제
			CObject::DeleteObject(destroyedComponent);
		}
		DestroyedComponents.clear();
	}

	// 사용되는 컴포넌트들의 Start() 메서드와 Tick() 메서드를 호출합니다.
	if (UsedComponents.size() > 0)
	{
		for (auto component : UsedComponents)
		{
			// 제거 대상인 경우 처리하지 않습니다.
			if (component->bBeDestroy) continue;

			// 아직 Start() 메서드가 호출된 GameObject 가 아니라면, Start() 메서드 호출
			if (!component->bIsStarted)
				component->Start();

			// Tick() 메서드를 사용하는 GameObject 라면, Tick() 메서드 호출
			if (component->bCanEverTick)
				component->Tick(DeltaSeconds);
		}
	}
}

void CGameObject::OnDestroy()
{
	// 생성된 컴포넌트가 존재한다면
	if (CreatedComponents.size() > 0)
	{
		// 생성된 모든 컴포넌트를 제거 대상으로 설정합니다.
		for (auto createdComponent : CreatedComponents)
			RemoveComponent(createdComponent);
	}

	// 사용중인 컴포넌트가 존재한다면
	if (UsedComponents.size() > 0)
	{
		// 사용중인 모든 컴포넌트를 제거 대상으로 설정합니다.
		for (auto component : UsedComponents)
			RemoveComponent(component);
	}
}

void CGameObject::Release()
{
	super::Release();

	CreatedComponents.clear();
	UsedComponents.clear();

	// 제거 대상인 컴포넌트들을 해제합니다.
	if (DestroyedComponents.size() > 0)
	{
		// 메모리 해제
		for (auto destroyedComponent : DestroyedComponents)
			CObject::DeleteObject(destroyedComponent);

		DestroyedComponents.clear();
	}

}

void CGameObject::RegisterNewRenderComponent(
	CRenderComponent* newRenderComponent)
{ OwnerScene->RegisterNewRenderComponent(newRenderComponent); }

void CGameObject::RemoveComponent(CComponent* component)
{
	// 이미 제거 대상이 되어있는 컴포넌트라면 제거 작업을 중단합니다.
	if (component->bBeDestroy) return;

	// 제거 대상으로 설정합니다.
	component->bBeDestroy = true;
	DestroyedComponents.push_back(component);
}

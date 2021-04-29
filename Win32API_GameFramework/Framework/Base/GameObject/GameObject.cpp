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
	// ������ ������Ʈ�� �����Ѵٸ�
	if (CreatedComponents.size() > 0)
	{
		// ���Ǵ� ������Ʈ ����Ʈ�� �߰��մϴ�.
		for (auto createdComponent : CreatedComponents)
			UsedComponents.push_back(createdComponent);
		CreatedComponents.clear();
	}

	// ���ŵ� ������Ʈ�� �����Ѵٸ�
	if (DestroyedComponents.size() > 0)
	{
		for (auto destroyedComponent : DestroyedComponents)
		{
			// ������ų ������Ʈ�� ������� ������Ʈ�鿡�� �����մϴ�.
			UsedComponents.remove(destroyedComponent);

			// �޸� ����
			CObject::DeleteObject(destroyedComponent);
		}
		DestroyedComponents.clear();
	}

	// ���Ǵ� ������Ʈ���� Start() �޼���� Tick() �޼��带 ȣ���մϴ�.
	if (UsedComponents.size() > 0)
	{
		for (auto component : UsedComponents)
		{
			// ���� ����� ��� ó������ �ʽ��ϴ�.
			if (component->bBeDestroy) continue;

			// ���� Start() �޼��尡 ȣ��� GameObject �� �ƴ϶��, Start() �޼��� ȣ��
			if (!component->bIsStarted)
				component->Start();

			// Tick() �޼��带 ����ϴ� GameObject ���, Tick() �޼��� ȣ��
			if (component->bCanEverTick)
				component->Tick(DeltaSeconds);
		}
	}
}

void CGameObject::OnDestroy()
{
	// ������ ������Ʈ�� �����Ѵٸ�
	if (CreatedComponents.size() > 0)
	{
		// ������ ��� ������Ʈ�� ���� ������� �����մϴ�.
		for (auto createdComponent : CreatedComponents)
			RemoveComponent(createdComponent);
	}

	// ������� ������Ʈ�� �����Ѵٸ�
	if (UsedComponents.size() > 0)
	{
		// ������� ��� ������Ʈ�� ���� ������� �����մϴ�.
		for (auto component : UsedComponents)
			RemoveComponent(component);
	}
}

void CGameObject::Release()
{
	super::Release();

	CreatedComponents.clear();
	UsedComponents.clear();

	// ���� ����� ������Ʈ���� �����մϴ�.
	if (DestroyedComponents.size() > 0)
	{
		// �޸� ����
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
	// �̹� ���� ����� �Ǿ��ִ� ������Ʈ��� ���� �۾��� �ߴ��մϴ�.
	if (component->bBeDestroy) return;

	// ���� ������� �����մϴ�.
	component->bBeDestroy = true;
	DestroyedComponents.push_back(component);
}

#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Struct/Vector/Vector.h"

#include "Framework/Single/CollisionManager/CollisionManager.h"

#include "Framework/Base/Component/RenderComponent/RenderComponent.h"

#include "Framework/Base/Component/Collision/CollisionComponent.h"

class CGameObject :
    public CObject
{
private :
	// �߰���ų ������Ʈ���� ��Ÿ���ϴ�.
	list<CComponent*> CreatedComponents;

	// �߰��Ǿ� ���Ǵ� ������Ʈ���� ��Ÿ���ϴ�.
	list<CComponent*> UsedComponents;

	// ���ŵ� ������Ʈ���� ��Ÿ���ϴ�.
	list<CComponent*> DestroyedComponents;

public :
	// �� ���� ������Ʈ�� �����ϴ� �� ��ü�� ��Ÿ���ϴ�.
	class CScene* OwnerScene;

	// ������Ʈ�� �̸�
	tstring Name;

	// �� ������Ʈ�� ��ġ
	FVector Position;

	// �� ������Ʈ�� Tick() �޼��带 ȣ���� �������� ���� ���θ� ��Ÿ���ϴ�.
	bool bCanEverTick;

	// �� ������Ʈ�� Start() �޼��尡 ȣ��Ǿ����� ��Ÿ���ϴ�.
	bool bIsStarted;

	// �� ������Ʈ�� ���� ������� ��Ÿ���ϴ�.
	bool bBeDestroy;

public :
	CGameObject();

public :
	// GameObject �� �����Ǿ��� ��� ������ ���� �� �� ȣ��Ǵ� �޼���
	virtual void Initialize() override;

	// GameObject ���� ���Ǵ� GameObject �� ��� �Ǿ��� ��� �ʱ�ȭ ���� �� �� ȣ��Ǵ� �޼���
	virtual void Start();

	// �� �����Ӹ��� ȣ��Ǵ� �޼���
	/// - DeltaSeconds : ������ ���� ���� �ð��� ���޵˴ϴ�.
	virtual void Tick(float DeltaSeconds);

	// GameObject �� ���� ����� �Ǿ��� ��� ȣ��Ǵ� �޼���
	virtual void OnDestroy();

	// GameObject �� �޸� ������ �� ȣ��Ǵ� �޼���
	virtual void Release() override;

private :
	void RegisterNewRenderComponent(CRenderComponent* newRenderComponent);

public :
	template<typename T>
	FORCEINLINE static T* NewObject(class CScene * ownerScene, tstring objName)
	{
		T* newObject = new T();
		newObject->OwnerScene = ownerScene;
		newObject->Name = objName;

		newObject->Initialize();

		return newObject;
	}

	// ������Ʈ�� �߰��մϴ�.
	template<typename ComponentClassType>
	ComponentClassType* AddComponent()
	{
		// CComponent Ŭ������ ��ӹ��� �ʴ´ٸ� ������Ʈ �߰��� �ߴ��մϴ�.
		if (!IsA<CComponent, ComponentClassType>())
		{
			LOG(ToTString(typeid(ComponentClassType).name()) << TEXT("�� CComponent �� ��� ���谡 �ƴմϴ�."));
			return nullptr;
		}

		// ������Ʈ�� �����մϴ�.
		CComponent* newComponent = CComponent::NewComponent<ComponentClassType>(this);
		CreatedComponents.push_back(newComponent);

		// ���� �߰��ϴ� ������Ʈ�� RenderComponent ���
		if (IsA<CRenderComponent, ComponentClassType>())
			RegisterNewRenderComponent(Cast<CRenderComponent>(newComponent));

		// ���� �߰��ϴ� ������Ʈ�� CollisionComponent ���
		else if (IsA<CCollisionComponent, ComponentClassType>())
			CCollisionManager::Instance()->RegisterCollision(Cast<CCollisionComponent>(newComponent));

		return Cast<ComponentClassType>(newComponent);
	}

	// ������Ʈ�� �����մϴ�.
	void RemoveComponent(CComponent* component);

	


};


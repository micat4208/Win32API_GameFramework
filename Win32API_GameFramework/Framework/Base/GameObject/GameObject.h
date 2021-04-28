#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Struct/Vector/Vector.h"

#include "Framework/Base/Component/Component.h"

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

};


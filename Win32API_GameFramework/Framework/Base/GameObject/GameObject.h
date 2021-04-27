#pragma once
#include "Framework/Base/Object/Object.h"

class CGameObject :
    public CObject
{
public :
	// �� ���� ������Ʈ�� �����ϴ� �� ��ü�� ��Ÿ���ϴ�.
	class CScene* OwnerScene;

	// ������Ʈ�� �̸�
	tstring Name;

	// �� ������Ʈ�� ���� ������� ��Ÿ���ϴ�.
	bool bBeDestroy;

public :
	CGameObject();


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


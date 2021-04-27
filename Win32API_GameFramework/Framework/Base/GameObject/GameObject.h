#pragma once
#include "Framework/Base/Object/Object.h"

class CGameObject :
    public CObject
{
public :
	// 이 게임 오브젝트를 소유하는 씬 객체를 나타냅니다.
	class CScene* OwnerScene;

	// 오브젝트의 이름
	tstring Name;

	// 이 오브젝트가 제거 대상임을 나타냅니다.
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


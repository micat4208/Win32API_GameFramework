#include "GameInstance.h"
#include "Framework/Single/SceneManager/SceneManager.h"

CGameInstance::CGameInstance()
{
}

void CGameInstance::Initialize()
{
	super::Initialize();

	// SceneManager 등록
	RegisterManagerClass<CSceneManager>();

}

void CGameInstance::Release()
{
	super::Release();

	// 등록시킨 SubManager 객체들을 해제합니다.
	for (auto iter = ManagerClasses.begin();
		iter != ManagerClasses.end(); ++iter)
	{
		iter->second->ReleaseManagerClass();

		delete iter->second;
		iter->second = nullptr;
		//CObject* managerInstance = Cast<CObject>(iter->second);
		//CObject::DeleteObject(managerInstance);
	}

	ManagerClasses.clear();
}

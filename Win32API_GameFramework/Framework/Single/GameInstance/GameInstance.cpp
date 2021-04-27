#include "GameInstance.h"
#include "Framework/Single/SceneManager/SceneManager.h"

CGameInstance::CGameInstance()
{
}

void CGameInstance::Initialize()
{
	super::Initialize();

	// SceneManager ���
	RegisterManagerClass<CSceneManager>();

}

void CGameInstance::Release()
{
	super::Release();

	// ��Ͻ�Ų SubManager ��ü���� �����մϴ�.
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

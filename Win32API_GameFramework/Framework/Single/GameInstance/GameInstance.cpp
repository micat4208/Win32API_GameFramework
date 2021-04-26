#include "GameInstance.h"

CGameInstance::CGameInstance()
{
}

void CGameInstance::Initialize()
{
	super::Initialize();

}

void CGameInstance::Release()
{
	super::Release();

	// ��Ͻ�Ų SubManager ��ü���� �����մϴ�.
	for (auto iter = ManagerClasses.begin();
		iter != ManagerClasses.end(); ++iter)
	{
		iter->second->ReleaseManagerClass();
		CObject::DeleteObject(iter->second);
	}

	ManagerClasses.clear();
}

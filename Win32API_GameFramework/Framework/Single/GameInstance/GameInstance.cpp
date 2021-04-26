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

	// 등록시킨 SubManager 객체들을 해제합니다.
	for (auto iter = ManagerClasses.begin();
		iter != ManagerClasses.end(); ++iter)
	{
		iter->second->ReleaseManagerClass();
		CObject::DeleteObject(iter->second);
	}

	ManagerClasses.clear();
}

#include "GameInstance.h"
#include "Framework/Single/SceneManager/SceneManager.h"
#include "Framework/Single/CollisionManager/CollisionManager.h"
#include "Framework/Single/InputManager/InputManager.h"

CGameInstance::CGameInstance()
{
}

void CGameInstance::Initialize()
{
	super::Initialize();

	Hdc = ::GetDC(Hwnd);
	GameInstance = this;


	// CollisionManager 등록
	RegisterManagerClass<CCollisionManager>();
	// InputManager 등록
	RegisterManagerClass<CInputManager>();
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

	GameInstance = nullptr;
	ReleaseDC(Hwnd, Hdc);
}

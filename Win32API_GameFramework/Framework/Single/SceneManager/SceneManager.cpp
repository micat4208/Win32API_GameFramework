#include "SceneManager.h"

#include "Game/Scene/GameScene/GameScene.h"
#include "Game/Scene/MapEditorScene/MapEditorScene.h"

CSceneManager::CSceneManager()
{
	CurrentScene = NextScene = nullptr;

	// 첫 번째 씬을 설정합니다.
	LoadScene<DEF_SCENE>();
}

void CSceneManager::ReleaseManagerClass()
{
	super::ReleaseManagerClass();

	CObject::DeleteObject(CurrentScene);
	CObject::DeleteObject(NextScene);
}

void CSceneManager::Tick(float deltaSeconds)
{
	// 다음 씬이 존재한다면
	if (NextScene != nullptr)
	{
		// 현재 플레이중인 씬이 존재한다면, 씬 해제
		if (CurrentScene != nullptr)
			CGameObject::DeleteObject(CurrentScene);

		// 씬 전환
		CurrentScene = NextScene;
		NextScene = nullptr;
	}

	if (CurrentScene != nullptr)
		CurrentScene->Tick(deltaSeconds);
}

void CSceneManager::Render(HDC hdc)
{
	if (CurrentScene != nullptr)
		CurrentScene->Render(hdc);
}

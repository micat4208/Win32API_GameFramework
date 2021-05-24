#include "SceneManager.h"

#include "Game/Scene/GameScene/GameScene.h"
#include "Game/Scene/MapEditorScene/MapEditorScene.h"

CSceneManager::CSceneManager()
{
	CurrentScene = NextScene = nullptr;

	// ù ��° ���� �����մϴ�.
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
	// ���� ���� �����Ѵٸ�
	if (NextScene != nullptr)
	{
		// ���� �÷������� ���� �����Ѵٸ�, �� ����
		if (CurrentScene != nullptr)
			CGameObject::DeleteObject(CurrentScene);

		// �� ��ȯ
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

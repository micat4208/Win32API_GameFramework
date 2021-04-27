#include "Scene.h"

void CScene::Initialize()
{
}

void CScene::Tick(float deltaSecond)
{
}

void CScene::Render(HDC hdc)
{
}

void CScene::Release()
{
}

void CScene::Destroy(CGameObject* gameObject)
{
	// 제거 대상인 경우 제거를 진행하지 않습니다.
	if (gameObject->bBeDestroy) return;

	// 제거 대상으로 설정합니다.
	gameObject->bBeDestroy = true;
	DestroyedGameObjectList.push_back(gameObject);
}

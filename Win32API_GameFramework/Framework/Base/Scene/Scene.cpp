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
	// ���� ����� ��� ���Ÿ� �������� �ʽ��ϴ�.
	if (gameObject->bBeDestroy) return;

	// ���� ������� �����մϴ�.
	gameObject->bBeDestroy = true;
	DestroyedGameObjectList.push_back(gameObject);
}

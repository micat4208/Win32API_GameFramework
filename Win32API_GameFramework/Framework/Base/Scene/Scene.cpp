#include "Scene.h"

#include "Framework/Bitmap/Bitmap.h"

void CScene::Initialize()
{
	super::Initialize();

	BackBuffer = CBitmap::LoadBmp(NewObject<CBitmap>(), TEXT("Resources/Default/Black.bmp"));
	Eraser = CBitmap::LoadBmp(NewObject<CBitmap>(), TEXT("Resources/Default/Black.bmp"));
}

void CScene::Tick(float deltaSecond)
{
	// ������ GameObject �� �����Ѵٸ�
	if (CreatedGameObjectList.size() > 0)
	{
		// ����ϴ� GameObject �� �߰��մϴ�.
		for (auto createdGameObject : CreatedGameObjectList)
			UsedGameObjectList.push_back(createdGameObject);
		CreatedGameObjectList.clear();
	}

	// ���ŵ� ���� ������Ʈ�� �����Ѵٸ�
	if (DestroyedGameObjectList.size() > 0)
	{
		for (auto destroyedGameObject : DestroyedGameObjectList)
		{
			// ����ϴ� GameObject ����Ʈ���� �����մϴ�.
			UsedGameObjectList.remove(destroyedGameObject);

			// �޸� ����
			CObject::DeleteObject(destroyedGameObject);
		}
		DestroyedGameObjectList.clear();
	}

	if (CreatedRenderComponents.size() > 0)
	{
		for (auto createdRenderComponent : CreatedRenderComponents)
			UsedRenderComponents.push_back(createdRenderComponent);
		CreatedRenderComponents.clear();
	}

	if (DestroyedRenderComponents.size() > 0)
	{
		for (auto destroyedRenderComponent : DestroyedRenderComponents)
			UsedRenderComponents.remove(destroyedRenderComponent);
		DestroyedRenderComponents.clear();
	}


	// ����ϴ� ������Ʈ�� �����ϴ� ���
	if (UsedGameObjectList.size() > 0)
	{
		for (auto gameObject : UsedGameObjectList)
		{
			// ���� ����̶�� �۾��� �ߴ��մϴ�.
			if (gameObject->bBeDestroy) continue;

			// Start() �޼��� ȣ��
			if (!gameObject->bIsStarted)
				gameObject->Start();

			// Tick() �޼��� ȣ��
			if (gameObject->bCanEverTick)
				gameObject->Tick(deltaSecond);
		}
	}
}

void CScene::Render(HDC hdc)
{
	BitBlt(BackBuffer->GetDC(), 0, 0, WND_WIDTH, WND_HEIGHT, Eraser->GetDC(), 0, 0, SRCCOPY);
	
	for (auto renderComponent : UsedRenderComponents)
	{
		if (renderComponent->bBeDestroy) continue;
		if (renderComponent->Owner->bBeDestroy) continue;
		if (!renderComponent->bUseRender) continue;
		if (!renderComponent->bIsStarted) continue;

		renderComponent->Render(BackBuffer->GetDC());
	}

	BitBlt(hdc, 0, 0, WND_WIDTH, WND_HEIGHT, BackBuffer->GetDC(), 0, 0, SRCCOPY);
}

void CScene::Release()
{
	super::Release();

	// �߰��Ϸ��� ������Ʈ�� �����ϴ� ���
	if (CreatedGameObjectList.size() > 0)
	{
		// ���� ������� �����մϴ�.
		for (auto createdGameObject : CreatedGameObjectList)
			Destroy(createdGameObject);
	}

	// ������� ������Ʈ���� ��� ���� ������� �����մϴ�.
	if (UsedGameObjectList.size() > 0)
	{
		for (auto gameObject : UsedGameObjectList)
			Destroy(gameObject);
	}

	// �޸� ����
	if (DestroyedGameObjectList.size() > 0)
	{
		for (auto destroyedGameObject : DestroyedGameObjectList)
			CGameObject::DeleteObject(destroyedGameObject);
	}

	CreatedGameObjectList.clear();
	UsedGameObjectList.clear();
	DestroyedGameObjectList.clear();

	// Bitmap ��ü ����
	CObject::DeleteObject(BackBuffer);
	CObject::DeleteObject(Eraser);
}

void CScene::Destroy(CGameObject* gameObject)
{
	// ���� ����� ��� ���Ÿ� �������� �ʽ��ϴ�.
	if (gameObject->bBeDestroy) return;

	// ���� ������� �����մϴ�.
	gameObject->bBeDestroy = true;

	gameObject->OnDestroy();

	DestroyedGameObjectList.push_back(gameObject);
}

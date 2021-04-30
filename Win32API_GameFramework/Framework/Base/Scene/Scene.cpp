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
	// 생성된 GameObject 가 존재한다면
	if (CreatedGameObjectList.size() > 0)
	{
		// 사용하는 GameObject 로 추가합니다.
		for (auto createdGameObject : CreatedGameObjectList)
			UsedGameObjectList.push_back(createdGameObject);
		CreatedGameObjectList.clear();
	}

	// 제거된 게임 오브젝트가 존재한다면
	if (DestroyedGameObjectList.size() > 0)
	{
		for (auto destroyedGameObject : DestroyedGameObjectList)
		{
			// 사용하는 GameObject 리스트에서 제외합니다.
			UsedGameObjectList.remove(destroyedGameObject);

			// 메모리 해제
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


	// 사용하는 오브젝트가 존재하는 경우
	if (UsedGameObjectList.size() > 0)
	{
		for (auto gameObject : UsedGameObjectList)
		{
			// 삭제 대상이라면 작업을 중단합니다.
			if (gameObject->bBeDestroy) continue;

			// Start() 메서드 호출
			if (!gameObject->bIsStarted)
				gameObject->Start();

			// Tick() 메서드 호출
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

	// 추가하려는 오브젝트가 존재하는 경우
	if (CreatedGameObjectList.size() > 0)
	{
		// 제거 대상으로 설정합니다.
		for (auto createdGameObject : CreatedGameObjectList)
			Destroy(createdGameObject);
	}

	// 사용중인 오브젝트들을 모두 제거 대상으로 설정합니다.
	if (UsedGameObjectList.size() > 0)
	{
		for (auto gameObject : UsedGameObjectList)
			Destroy(gameObject);
	}

	// 메모리 해제
	if (DestroyedGameObjectList.size() > 0)
	{
		for (auto destroyedGameObject : DestroyedGameObjectList)
			CGameObject::DeleteObject(destroyedGameObject);
	}

	CreatedGameObjectList.clear();
	UsedGameObjectList.clear();
	DestroyedGameObjectList.clear();

	// Bitmap 객체 해제
	CObject::DeleteObject(BackBuffer);
	CObject::DeleteObject(Eraser);
}

void CScene::Destroy(CGameObject* gameObject)
{
	// 제거 대상인 경우 제거를 진행하지 않습니다.
	if (gameObject->bBeDestroy) return;

	// 제거 대상으로 설정합니다.
	gameObject->bBeDestroy = true;

	gameObject->OnDestroy();

	DestroyedGameObjectList.push_back(gameObject);
}

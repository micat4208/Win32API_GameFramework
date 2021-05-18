#include "Scene.h"

#include "Framework/Bitmap/Bitmap.h"

#include "Framework/Statics/GameplayStatics.h"

void CScene::Initialize()
{
	super::Initialize();

	BackBuffer = CBitmap::LoadBmp(NewObject<CBitmap>(), TEXT("Resources/Default/Black.bmp"));
	Eraser = CBitmap::LoadBmp(NewObject<CBitmap>(), TEXT("Resources/Default/Black.bmp"));

	bNeedSort = false;
	CameraPosition = FVector::ZeroVector();


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
		bNeedSort = true;

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
	if (bNeedSort)
	{ 
		UsedRenderComponents.sort([](CRenderComponent* first, CRenderComponent* second)
			{ return first->GetSortingOrder() < second->GetSortingOrder(); } );
	
		bNeedSort = false;
	}

	BitBlt(BackBuffer->GetDC(), 0, 0, WND_WIDTH, WND_HEIGHT, Eraser->GetDC(), 0, 0, SRCCOPY);

	// RenderComponent Draw
	for (auto renderComponent : UsedRenderComponents)
	{
		if (renderComponent->bBeDestroy) continue;
		if (renderComponent->Owner->bBeDestroy) continue;
		if (!renderComponent->bUseRender) continue;
		if (!renderComponent->bIsStarted) continue;

		renderComponent->Render(BackBuffer->GetDC());
	}

#if GAME_DEBUG_MODE == true
	// Debug Draw
	for (auto debugDrawInfo : DebugDrawInfos)
		debugDrawInfo->Draw(BackBuffer->GetDC());

	// Delete Debug Draw Info
	for (auto iter = DebugDrawInfos.begin(); iter != DebugDrawInfos.end(); ++iter)
	{
		// 그리기 시작 후 Duration 만큼의 시간이 지났다면 메모리 해제, nullptr 로 초기화
		if (CGameplayStatics::GetTime() - (*iter)->DrawStartTime >= (*iter)->Duration)
			CObject::DeleteObject(*iter);
	}

	// nullptr 인 요소들을 제거
	DebugDrawInfos.remove_if([](FDebugDrawInfo* debugDrawInfo) 
		{ return debugDrawInfo == nullptr; });
#endif


	BitBlt(hdc, 0, 0, WND_WIDTH, WND_HEIGHT, BackBuffer->GetDC(), 0, 0, SRCCOPY);
}

void CScene::Release()
{
	super::Release();


#if GAME_DEBUG_MODE == true
	for (auto iter = DebugDrawInfos.begin(); iter != DebugDrawInfos.end(); ++iter)
		CObject::DeleteObject(*iter);
	DebugDrawInfos.clear();
#endif



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

void CScene::AddDebugDraw(
	EDebugDrawType debugDrawType, 
	FVector vec1, 
	FVector vec2, 
	COLORREF color, 
	float duration,
	bool bFill)
{
#if GAME_DEBUG_MODE == true

	FDebugDrawInfo* newDebugDrawInfo = CObject::NewObject<FDebugDrawInfo>();

	newDebugDrawInfo->InitializeDebugDrawInfo(
		debugDrawType, vec1, vec2, color, duration, bFill);

	DebugDrawInfos.push_back(newDebugDrawInfo);

#endif
}

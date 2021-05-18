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
		// �׸��� ���� �� Duration ��ŭ�� �ð��� �����ٸ� �޸� ����, nullptr �� �ʱ�ȭ
		if (CGameplayStatics::GetTime() - (*iter)->DrawStartTime >= (*iter)->Duration)
			CObject::DeleteObject(*iter);
	}

	// nullptr �� ��ҵ��� ����
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

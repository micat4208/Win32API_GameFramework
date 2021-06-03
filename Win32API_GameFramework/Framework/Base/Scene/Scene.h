#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Base/GameObject/GameObject.h"

#include "Framework/Struct/DebugDrawInfo/DebugDrawInfo.h"

class CScene abstract :
    public CObject
{

private :
    // 이 씬에서 사용되는 GameObject 들을 나타냅니다.
    list<CGameObject*> UsedGameObjectList;

    // 생성된 GameObject 들을 나타냅니다.
    list<CGameObject*> CreatedGameObjectList;

    // 제거될 GameObject 들을 나타냅니다.
    list<CGameObject*> DestroyedGameObjectList;

    // 생성된 RenderComponent 들을 나타냅니다.
    list<class CRenderComponent*> CreatedRenderComponents;

    // 그리기 작업이 진행되는 RenderComponent 들을 나타냅니다.
    list<class CRenderComponent*> UsedRenderComponents;

    // 제거된 RenerComponent 들을 나타냅니다.
    list<class CRenderComponent*> DestroyedRenderComponents;

    // DebugDrawInfos
    list<struct FDebugDrawInfo*> DebugDrawInfos;

    class CBitmap* BackBuffer, *Eraser;

    FThread* SortingOrderThread;
    bool bDoSortRenderComponent;

    class CScreenObject* Screen;

public :
    // UsedRenderComponents 에 추가된 요소들의 정렬이 필요함을 나타냅니다.
    bool bNeedSort;

    // 카메라 위치를 나타냅니다.
    FVector CameraPosition;

private:
    void SortRenderComponent();

public :
    virtual void Initialize() override;

    // 매 프레임마다 호출되는 메서드입니다.
    /// - deltaSecond : 프레임 사이 간격 시간이 전달됩니다.
    virtual void Tick(float deltaSecond);

    virtual void Render(HDC hdc);

    virtual void Release() override;

public :
    template<typename T>
    FORCEINLINE T* NewGameObject(
        tstring objName = tstring(TEXT("New GameObject")))
    {
        // 상속 관계를 확인합니다.
        if (!IsA<CGameObject, T>())
        {
            LOGF(ToTString(typeid(T).name()) << TEXT(" 형식은 CGameObject 형식이 아닙니다."));
            return nullptr;
        }

        // 새로운 GameObject 를 생성합니다.
        T* newGameObject = CGameObject::NewObject<T>(this, objName);
        CreatedGameObjectList.push_back(newGameObject);

        // 생성한 GameObject 를 반환합니다.
        return newGameObject;
    }

    // 오브젝트를 제거합니다.
    void Destroy(CGameObject* gameObject);

    FORCEINLINE void RegisterNewRenderComponent(
        class CRenderComponent * newRenderComponent)
    { CreatedRenderComponents.push_back(newRenderComponent); }

    FORCEINLINE void UnRegisterRenderComponent(
        class CRenderComponent* renderComponent)
    { DestroyedRenderComponents.push_back(renderComponent); }

    FORCEINLINE void DrawCircle(FVector center, FVector size,
        COLORREF color, float duration = 5.0f, bool bFill = false)
    { AddDebugDraw(EDebugDrawType::DT_Circle, center, size, color, duration, bFill); }

    FORCEINLINE void DrawRect(FVector center, FVector size,
        COLORREF color, float duration = 5.0f, bool bFill = false)
    { AddDebugDraw(EDebugDrawType::DT_Rect, center, size, color, duration, bFill); }

    FORCEINLINE void DrawLine(FVector start, FVector end,
        COLORREF color, float duration = 5.0f, bool bFill = false)
    { AddDebugDraw(EDebugDrawType::DT_LINE, start, end, color, duration, bFill); }

    FORCEINLINE void MoveCamera(FVector velocity)
    { CameraPosition += (velocity * -1.0f); }

    FORCEINLINE class CScreenObject* GetScreen() const
    { return Screen; }


private :
    void AddDebugDraw(EDebugDrawType debugDrawType, FVector vec1, FVector vec2,
        COLORREF color, float duration, bool bFill);

};


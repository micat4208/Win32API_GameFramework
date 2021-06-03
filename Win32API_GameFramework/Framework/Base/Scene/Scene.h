#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Base/GameObject/GameObject.h"

#include "Framework/Struct/DebugDrawInfo/DebugDrawInfo.h"

class CScene abstract :
    public CObject
{

private :
    // �� ������ ���Ǵ� GameObject ���� ��Ÿ���ϴ�.
    list<CGameObject*> UsedGameObjectList;

    // ������ GameObject ���� ��Ÿ���ϴ�.
    list<CGameObject*> CreatedGameObjectList;

    // ���ŵ� GameObject ���� ��Ÿ���ϴ�.
    list<CGameObject*> DestroyedGameObjectList;

    // ������ RenderComponent ���� ��Ÿ���ϴ�.
    list<class CRenderComponent*> CreatedRenderComponents;

    // �׸��� �۾��� ����Ǵ� RenderComponent ���� ��Ÿ���ϴ�.
    list<class CRenderComponent*> UsedRenderComponents;

    // ���ŵ� RenerComponent ���� ��Ÿ���ϴ�.
    list<class CRenderComponent*> DestroyedRenderComponents;

    // DebugDrawInfos
    list<struct FDebugDrawInfo*> DebugDrawInfos;

    class CBitmap* BackBuffer, *Eraser;

    FThread* SortingOrderThread;
    bool bDoSortRenderComponent;

    class CScreenObject* Screen;

public :
    // UsedRenderComponents �� �߰��� ��ҵ��� ������ �ʿ����� ��Ÿ���ϴ�.
    bool bNeedSort;

    // ī�޶� ��ġ�� ��Ÿ���ϴ�.
    FVector CameraPosition;

private:
    void SortRenderComponent();

public :
    virtual void Initialize() override;

    // �� �����Ӹ��� ȣ��Ǵ� �޼����Դϴ�.
    /// - deltaSecond : ������ ���� ���� �ð��� ���޵˴ϴ�.
    virtual void Tick(float deltaSecond);

    virtual void Render(HDC hdc);

    virtual void Release() override;

public :
    template<typename T>
    FORCEINLINE T* NewGameObject(
        tstring objName = tstring(TEXT("New GameObject")))
    {
        // ��� ���踦 Ȯ���մϴ�.
        if (!IsA<CGameObject, T>())
        {
            LOGF(ToTString(typeid(T).name()) << TEXT(" ������ CGameObject ������ �ƴմϴ�."));
            return nullptr;
        }

        // ���ο� GameObject �� �����մϴ�.
        T* newGameObject = CGameObject::NewObject<T>(this, objName);
        CreatedGameObjectList.push_back(newGameObject);

        // ������ GameObject �� ��ȯ�մϴ�.
        return newGameObject;
    }

    // ������Ʈ�� �����մϴ�.
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


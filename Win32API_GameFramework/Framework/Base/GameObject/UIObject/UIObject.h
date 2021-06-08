#pragma once
#include "Base/GameObject/GameObject.h"

#include "Struct/Rect/Rect.h"

CLASS(CUIObject, CGameObject)
class CUIObject :
    public CGameObject
{
    USE_CLASS(CUIObject);

public :
    class CScreenObject* ScreenObject;

protected :
    list<interface IUIComponent*> UIComponents;

    FRect Bounds;
    FVector Size;
    FVector Anchor;
    FVector Pivot;

public :
    virtual void Initialize() override;
    /// - 필드 ScreenObject 는 OnUIObjectCreated() 메서드가 호출될 때 설정되므로
    ///   이 메서드 내에서 사용되어서는 안됩니다.

    // UIObject 가 생성되고 UIObjects 에 추가된 후 호출되는 메서드입니다.
    /// - 이곳에서 ScreenObject 에 대한 값이 할당됩니다.
    /// - UI 오브젝트의 바운더리가 이 메서드가 호출될 때 설정됩니다.
    virtual void OnUIObjectCreated();

    // 화면을 기준으로 하는 UIObject 의 Boundary 를 갱신합니다.
    void UpdateUIObjectBoundary();

    template<typename T>
    T* AddUIComponent()
    {
        T* newUIComponent = AddComponent<T>();
        UIComponents.push_back(newUIComponent);

        return newUIComponent;
    }


public :
    FORCEINLINE void SetAnchor(FVector newAnchor)
    {
        Anchor = newAnchor;
        UpdateUIObjectBoundary();
    }

    FORCEINLINE FVector GetAnchor() const
    { return Anchor; }

    FORCEINLINE void SetPivot(FVector newPivot)
    {
        Pivot = newPivot;
        UpdateUIObjectBoundary();
    }

    FORCEINLINE FVector GetPivot() const
    { return Pivot; }

    FORCEINLINE void SetSize(FVector newSize)
    {
        Size = newSize;
        UpdateUIObjectBoundary();
    }

    FORCEINLINE FVector GetSize() const
    { return Size; }

    // UIObject 의 바운더리를 얻습니다.
    FORCEINLINE FRect GetBounds() const
    { return Bounds; }


};


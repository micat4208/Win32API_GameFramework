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
    /// - �ʵ� ScreenObject �� OnUIObjectCreated() �޼��尡 ȣ��� �� �����ǹǷ�
    ///   �� �޼��� ������ ���Ǿ�� �ȵ˴ϴ�.

    // UIObject �� �����ǰ� UIObjects �� �߰��� �� ȣ��Ǵ� �޼����Դϴ�.
    /// - �̰����� ScreenObject �� ���� ���� �Ҵ�˴ϴ�.
    /// - UI ������Ʈ�� �ٿ������ �� �޼��尡 ȣ��� �� �����˴ϴ�.
    virtual void OnUIObjectCreated();

    // ȭ���� �������� �ϴ� UIObject �� Boundary �� �����մϴ�.
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

    // UIObject �� �ٿ������ ����ϴ�.
    FORCEINLINE FRect GetBounds() const
    { return Bounds; }


};


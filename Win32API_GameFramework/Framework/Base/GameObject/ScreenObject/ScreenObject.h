#pragma once
#include "Base/GameObject/GameObject.h"
#include "Base/Scene/Scene.h"
#include "Struct/Rect/Rect.h"

class CScreenObject :
    public CGameObject
{
private :
    // ȭ�� Boundary �� ��Ÿ���ϴ�.
    FRect ScreenBounds;

    list<class CUIObject*> UIObjects;


public :
    CScreenObject();

private :
    void AddUIObject(class CUIObject* newUIObject);

public :
    // UIObject �� �����մϴ�.
    template<typename T>
    FORCEINLINE T* CreateUIObject(tstring objectName = TEXT("New UI Object"))
    {
        T * newUIObject = OwnerScene->NewGameObject<T>(objectName);

        AddUIObject(newUIObject);

        return newUIObject;
    }


    // UIObject �� �����մϴ�.
    /// - uiObject : ������ UIObject �� �����մϴ�.
    void DestroyUIObject(class CUIObject* uiObject);

    FORCEINLINE const FRect& GetScreenBounds() const
    { return ScreenBounds; }

    FORCEINLINE void SetScreenBounds(FRect newScreenBounds)
    { ScreenBounds = newScreenBounds; }

};


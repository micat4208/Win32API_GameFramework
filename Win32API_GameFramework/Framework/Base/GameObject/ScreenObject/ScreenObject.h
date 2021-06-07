#pragma once
#include "Base/GameObject/GameObject.h"
#include "Base/Scene/Scene.h"
#include "Struct/Rect/Rect.h"

class CScreenObject :
    public CGameObject
{
private :
    // 화면 Boundary 를 나타냅니다.
    FRect ScreenBounds;

    list<class CUIObject*> UIObjects;


public :
    CScreenObject();

private :
    void AddUIObject(class CUIObject* newUIObject);

public :
    // UIObject 를 생성합니다.
    template<typename T>
    FORCEINLINE T* CreateUIObject(tstring objectName = TEXT("New UI Object"))
    {
        T * newUIObject = OwnerScene->NewGameObject<T>(objectName);

        AddUIObject(newUIObject);

        return newUIObject;
    }


    // UIObject 를 제거합니다.
    /// - uiObject : 제거할 UIObject 를 전달합니다.
    void DestroyUIObject(class CUIObject* uiObject);

    FORCEINLINE const FRect& GetScreenBounds() const
    { return ScreenBounds; }

    FORCEINLINE void SetScreenBounds(FRect newScreenBounds)
    { ScreenBounds = newScreenBounds; }

};


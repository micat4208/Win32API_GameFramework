#pragma once
#include "Base/GameObject/GameObject.h"
#include "Base/Scene/Scene.h"

class CScreenObject :
    public CGameObject
{
private :
    list<class CUIObject*> UIObjects;

public :
    // UIObject 를 생성합니다.
    template<typename T>
    FORCEINLINE T* CreateUIObject(tstring objectName = TEXT("New UI Object"))
    {
        T * newUIObject = OwnerScene->NewGameObject<T>(objectName);

        UIObjects.push_back(newUIObject);

        return newUIObject;
    }

    // UIObject 를 제거합니다.
    /// - uiObject : 제거할 UIObject 를 전달합니다.
    void DestroyUIObject(class CUIObject* uiObject);

};


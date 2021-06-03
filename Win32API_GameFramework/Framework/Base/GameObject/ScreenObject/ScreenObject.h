#pragma once
#include "Base/GameObject/GameObject.h"
#include "Base/Scene/Scene.h"

class CScreenObject :
    public CGameObject
{
private :
    list<class CUIObject*> UIObjects;

public :
    // UIObject �� �����մϴ�.
    template<typename T>
    FORCEINLINE T* CreateUIObject(tstring objectName = TEXT("New UI Object"))
    {
        T * newUIObject = OwnerScene->NewGameObject<T>(objectName);

        UIObjects.push_back(newUIObject);

        return newUIObject;
    }

    // UIObject �� �����մϴ�.
    /// - uiObject : ������ UIObject �� �����մϴ�.
    void DestroyUIObject(class CUIObject* uiObject);

};


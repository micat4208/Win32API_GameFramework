#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Base/GameObject/GameObject.h"

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


};


#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Base/GameObject/GameObject.h"

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


};


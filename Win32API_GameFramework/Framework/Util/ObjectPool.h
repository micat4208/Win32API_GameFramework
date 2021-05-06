#pragma once
#include "Framework/Base/Object/Object.h"

#include "Framework/Interface/ObjectPoolable.h"

// ������Ʈ Ǯ���� �����ϴ� Ŭ����
class CObjectPool final :
    public CObject
{
private :
    // Ǯ����ų ��ü���� ������ �����̳�
    vector<IObjectPoolable*> PoolObjects;

public:
    // Ǯ����ų ���ο� ��ü�� ����մϴ�.
    template<typename T>
    FORCEINLINE T* RegisterRecyclableObject(T* newRecyclableObject)
    {
        LOG(TEXT("PoolObjects.size() = ") << PoolObjects.size());

        PoolObjects.push_back(newRecyclableObject);
        return newRecyclableObject;
    }

    // ��Ȱ��� ��ü�� ����ϴ�.
    template<typename T>
    T* GetRecycledObject()
    { return GetRecycledObject<T>([](T* obj) { return true; }); }

    // ��Ȱ��� ��ü�� ����ϴ�.
    template<typename T>
    T* GetRecycledObject(function<bool(T* poolableObject)> pred)
    {
        // ����� ������ 0 �̶�� nullptr ��ȯ
        if (PoolObjects.size() == 0) return nullptr;

        for (auto obj : PoolObjects)
        {
            if (obj->GetCanRecyclable())
            {
                if (!pred(Cast<T>(obj))) continue;

                obj->SetCanRecyclable(false);
                obj->OnRecycleStarted();
                return Cast<T>(obj);
            }
        }

        return nullptr;
    }

public :
    virtual void Release() override;
};


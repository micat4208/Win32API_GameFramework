#pragma once
#include "Framework/Base/Object/Object.h"

#include "Framework/Interface/ObjectPoolable.h"

// 오브젝트 풀링을 수행하는 클래스
class CObjectPool final :
    public CObject
{
private :
    // 풀링시킬 객체들을 저장할 컨테이너
    vector<IObjectPoolable*> PoolObjects;

public:
    // 풀링시킬 새로운 객체를 등록합니다.
    template<typename T>
    FORCEINLINE T* RegisterRecyclableObject(T* newRecyclableObject)
    {
        LOG(TEXT("PoolObjects.size() = ") << PoolObjects.size());

        PoolObjects.push_back(newRecyclableObject);
        return newRecyclableObject;
    }

    // 재활용된 객체를 얻습니다.
    template<typename T>
    T* GetRecycledObject()
    { return GetRecycledObject<T>([](T* obj) { return true; }); }

    // 재활용된 객체를 얻습니다.
    template<typename T>
    T* GetRecycledObject(function<bool(T* poolableObject)> pred)
    {
        // 요소의 개수가 0 이라면 nullptr 반환
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


#pragma once

#include "Framework/Base/Object/Object.h"
#include "Framework/Struct/Vector/Vector.h"

// 어떠한 물체의 기능을 나타낼 때 사용되는 클래스
class CComponent abstract :
    public CObject
{

public :
    // 해당 컴포넌트를 소유하는 오브젝트를 나타냅니다.
    class CGameObject* Owner;

    // Tick() 메서드 사용 여부를 나타냅니다.
    bool bCanEverTick;

    // Start() 메서드가 호출되었음을 나타냅니다.
    bool bIsStarted;

    // 이 컴포넌트가 제거 대상임을 나타냅니다.
    bool bBeDestroy;

public :
    CComponent();

public :
    virtual void Start();
    FORCEINLINE virtual void Tick(float deltaSeconds) {};

public :

    // T 형식의 Component 를 생성합니다.
    template<typename T>
    FORCEINLINE static T* NewComponent(class CGameObject * ownerGameObject)
    {
        if (!IsA<CComponent, T>()) return nullptr;

        T* newComponent = new T();
        newComponent->Owner = ownerGameObject;
        newComponent->Initialize();

        return newComponent;
    }
};


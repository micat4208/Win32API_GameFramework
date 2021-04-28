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

public :
    CComponent();

public :
    virtual void Start();
    FORCEINLINE virtual void Tick(float deltaSeconds) {};
};


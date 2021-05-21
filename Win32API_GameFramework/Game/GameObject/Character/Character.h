#pragma once
#include "Framework/Base/GameObject/GameObject.h"

class CCharacter abstract :
    public CGameObject
{
protected :
    // 이동 기능을 제공하는 컴포넌트를 나타냅니다.
    class CMovementComponent* Movement;

public :
    virtual void Initialize() override;

public :
    FORCEINLINE class CMovementComponent* GetMovement() const
    { return Movement; }
};


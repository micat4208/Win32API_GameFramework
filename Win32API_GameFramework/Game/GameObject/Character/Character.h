#pragma once
#include "Framework/Base/GameObject/GameObject.h"

class CCharacter abstract :
    public CGameObject
{
protected :
    // 캐릭터 이동 기능을 제공하는 컴포넌트를 나타냅니다.
    class CCharacterMovementComponent* CharacterMovement;

public :
    virtual void Initialize() override;


};


#pragma once
#include "Game/GameObject/Character/Character.h"

class CPlayerCharacter final :
    public CCharacter
{



private :
    class CSpriteAnimationComponent* SpriteAnimation;
    class CPlayerCharacterMovementHelperComponent* MovementHelper;

    // 키 입력값을 저장합니다.
    FVector InputAxis;

public :
    virtual void Initialize() override;
    virtual void Start() override;

    virtual void Tick(float dt) override;
    virtual void Release() override;

private :
    void InputKey(float dt);

    void FloatingPlayerUI();

public :
    FORCEINLINE class CMovementComponent* GetMovement() const
    { return Movement; }

    FORCEINLINE class CPlayerCharacterMovementHelperComponent* GetMovementHelper() const
    { return MovementHelper; }

    FORCEINLINE FVector GetInputAxis() const
    { return InputAxis; }
};


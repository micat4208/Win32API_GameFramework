#pragma once
#include "Framework/Base/GameObject/GameObject.h"

class CCharacter abstract :
    public CGameObject
{
protected :
    // ĳ���� �̵� ����� �����ϴ� ������Ʈ�� ��Ÿ���ϴ�.
    class CCharacterMovementComponent* CharacterMovement;

public :
    virtual void Initialize() override;


};


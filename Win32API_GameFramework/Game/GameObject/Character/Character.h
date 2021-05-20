#pragma once
#include "Framework/Base/GameObject/GameObject.h"

class CCharacter abstract :
    public CGameObject
{
protected :
    // �̵� ����� �����ϴ� ������Ʈ�� ��Ÿ���ϴ�.
    class CMovementComponent* Movement;

public :
    virtual void Initialize() override;

};


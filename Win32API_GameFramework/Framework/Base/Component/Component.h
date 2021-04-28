#pragma once

#include "Framework/Base/Object/Object.h"
#include "Framework/Struct/Vector/Vector.h"

// ��� ��ü�� ����� ��Ÿ�� �� ���Ǵ� Ŭ����
class CComponent abstract :
    public CObject
{

public :
    // �ش� ������Ʈ�� �����ϴ� ������Ʈ�� ��Ÿ���ϴ�.
    class CGameObject* Owner;

    // Tick() �޼��� ��� ���θ� ��Ÿ���ϴ�.
    bool bCanEverTick;

    // Start() �޼��尡 ȣ��Ǿ����� ��Ÿ���ϴ�.
    bool bIsStarted;

public :
    CComponent();

public :
    virtual void Start();
    FORCEINLINE virtual void Tick(float deltaSeconds) {};
};


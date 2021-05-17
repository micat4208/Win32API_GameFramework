#pragma once
#include "Framework/Base/Component/Component.h"

// GameObject �� �������� Ư���� ��ġ, ũ�⸦ ���� ������Ʈ�Դϴ�.
class CSceneComponent :
    public CComponent
{
public :
    // ��� ��ġ�� ��Ÿ���ϴ�.
    FVector RelativePosition;

    // ��� ũ�⸦ ��Ÿ���ϴ�.
    FVector RelativeScale;

public :
    CSceneComponent();

public :
    // �� ������Ʈ�� ���� ��ġ�� ��ȯ�մϴ�.
    FVector GetComponentPosition() const;
};


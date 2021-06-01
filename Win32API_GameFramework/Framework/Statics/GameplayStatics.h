#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Struct/Vector/Vector.h"

// ���� �÷��̿� �ʿ��� ���� �޼��带 �����ϴ� ��ƿ Ŭ����
class CGameplayStatics final :
    public CObject
{
public :   
    // ���� ���� ���� ���� �ð��� ��ȯ�մϴ�.
    static float GetTime();

    // ���콺 ��ġ�� ��ȯ�մϴ�.
    /// - translated : Ŭ���̾�Ʈ ���� ���� ��ġ�� ��ȯ���� ��ȯ�� �������� �����մϴ�.
    static FVector GetMousePosition(bool translated = true);

};


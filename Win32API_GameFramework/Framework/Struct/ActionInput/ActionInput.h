#pragma once
#include "Framework/Base/Object/Object.h"

struct FActionInput final :
    public CObject
{
public :
    vector<int> ActionKeys;

    // ���ο� �Է� ���·� ���ŵ��� ��Ÿ���ϴ�.
    bool bUpdatedNewInputState;

    // ���� �Էµ� ���¸� ��Ÿ���ϴ�.
    bool bPrevInputState;

    // �Էµ��� ��Ÿ���ϴ�.
    bool bIsInput;

public :
    FActionInput() {}
    FActionInput(int actionKey);
    FActionInput(vector<int> actionKeys);

public :
    void UpdateInputActionValue();

    FORCEINLINE bool IsKeyDown()
    {
        if (!bUpdatedNewInputState) return false;
        return bIsInput;
    }

    FORCEINLINE bool IsKeyUp()
    {
        if (!bUpdatedNewInputState) return false;
        return !bIsInput;
    }

    FORCEINLINE bool IsKey()
    {
        return bIsInput;
    }

};


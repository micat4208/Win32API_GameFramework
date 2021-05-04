#pragma once
#include "Framework/Base/Object/Object.h"

struct FActionInput final :
    public CObject
{
public :
    vector<int> ActionKeys;

    // 새로운 입력 상태로 갱신됨을 나타냅니다.
    bool bUpdatedNewInputState;

    // 이전 입력됨 상태를 나타냅니다.
    bool bPrevInputState;

    // 입력됨을 나타냅니다.
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


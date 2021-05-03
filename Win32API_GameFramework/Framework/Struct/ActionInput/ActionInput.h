#pragma once
#include "Framework/Base/Object/Object.h"

struct FActionInput final :
    public CObject
{
public :
    vector<int> ActionKeys;

public :
    FActionInput() {}
    FActionInput(int actionKey);
    FActionInput(vector<int> actionKeys);

public :

    void UpdateInputActionValue();
};


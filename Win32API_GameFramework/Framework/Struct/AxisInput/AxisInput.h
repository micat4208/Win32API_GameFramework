#pragma once
#include "Framework/Base/Object/Object.h"

struct FAxisInput final :
    public CObject
{
public :
    // 축 입력 값
    float AxisValue;

    // 입력되었을 경우 -1, 1 로 설정될 키들
    vector<int> LowKey, HighKey;

public :
    FAxisInput() {}
    FAxisInput(int lowKey, int highKey);
    FAxisInput(vector<int> lowKeys, vector<int> highKeys);

public :
    // 축 입력 값을 갱신합니다.
    void UpdateInputAxisValue();
};


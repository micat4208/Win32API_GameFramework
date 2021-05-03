#pragma once
#include "Framework/Base/Object/Object.h"

struct FAxisInput final :
    public CObject
{
public :
    // �� �Է� ��
    float AxisValue;

    // �ԷµǾ��� ��� -1, 1 �� ������ Ű��
    vector<int> LowKey, HighKey;

public :
    FAxisInput() {}
    FAxisInput(int lowKey, int highKey);
    FAxisInput(vector<int> lowKeys, vector<int> highKeys);

public :
    // �� �Է� ���� �����մϴ�.
    void UpdateInputAxisValue();
};


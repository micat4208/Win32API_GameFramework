#pragma once
#include "Framework/Single/ManagerClassBase/ManagerClassBase.h"

#include "Framework/Struct/AxisInput/AxisInput.h"
#include "Framework/Struct/ActionInput/ActionInput.h"

#ifndef VK_KEY_DEF
#define VK_KEY_DEF

#define VK_A        0x41
#define VK_D        0x44
#define VK_S        0x53
#define VK_W        0x57

#endif

// �Է��� �����մϴ�.
typedef class CInputManager final :
    public CManagerClassBase<CInputManager>
{
private :
    // �� �Է��� �����մϴ�.
    map<tstring, FAxisInput> AxisInputs;

    // �׼� �Է��� �����մϴ�.
    map<tstring, FActionInput> ActionInputs;

public :
    // �Է� Ű���� ���ε���ŵ�ϴ�.
    virtual void InitializeManagerClass() override;

private :
    // �� �Է��� �߰��մϴ�.
    void AddAxis(tstring axisName, int lowKey, int highKey);
    void AddAxis(tstring axisName, vector<int> lowKeys, vector<int> highKeys);

    // �׼� �Է��� �߰��մϴ�.
    void AddAction(tstring actionName, int actionKey);
    void AddAction(tstring actionName, vector<int> actionKeys);

public :
    // �Է� ������ ���Ž�ŵ�ϴ�.
    void UpdateInputValue();

public :
    // �� �Է� ���� ����ϴ�.
    static float GetAxis(tstring axisName);

} CInput;


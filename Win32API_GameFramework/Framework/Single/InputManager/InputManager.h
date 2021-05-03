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

// 입력을 관리합니다.
typedef class CInputManager final :
    public CManagerClassBase<CInputManager>
{
private :
    // 축 입력을 저장합니다.
    map<tstring, FAxisInput> AxisInputs;

    // 액션 입력을 저장합니다.
    map<tstring, FActionInput> ActionInputs;

public :
    // 입력 키들을 바인딩시킵니다.
    virtual void InitializeManagerClass() override;

private :
    // 축 입력을 추가합니다.
    void AddAxis(tstring axisName, int lowKey, int highKey);
    void AddAxis(tstring axisName, vector<int> lowKeys, vector<int> highKeys);

    // 액션 입력을 추가합니다.
    void AddAction(tstring actionName, int actionKey);
    void AddAction(tstring actionName, vector<int> actionKeys);

public :
    // 입력 값들을 갱신시킵니다.
    void UpdateInputValue();

public :
    // 축 입력 값을 얻습니다.
    static float GetAxis(tstring axisName);

} CInput;


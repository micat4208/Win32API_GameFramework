#include "InputManager.h"

void CInputManager::InitializeManagerClass()
{
#pragma region Horizontal Axis ...
	vector<int> horizontalLow;
	horizontalLow.push_back(VK_LEFT);
	horizontalLow.push_back(VK_A);

	vector<int> horizontalHigh;
	horizontalHigh.push_back(VK_RIGHT);
	horizontalHigh.push_back(VK_D);

	AddAxis(TEXT("Horizontal"), horizontalLow, horizontalHigh);
#pragma endregion

#pragma region Vertical Axis ...
	vector<int> verticalLow;
	verticalLow.push_back(VK_UP);
	verticalLow.push_back(VK_W);

	vector<int> verticalHigh;
	verticalHigh.push_back(VK_DOWN);
	verticalHigh.push_back(VK_S);

	AddAxis(TEXT("Vertical"), verticalLow, verticalHigh);
#pragma endregion
}

void CInputManager::AddAxis(tstring axisName, int lowKey, int highKey)
{
	vector<int> lowKeys;
	lowKeys.push_back(lowKey);
	vector<int> highKeys;
	highKeys.push_back(highKey);

	AddAxis(axisName, lowKeys, highKeys);
}

void CInputManager::AddAxis(tstring axisName, vector<int> lowKeys, vector<int> highKeys)
{
	AxisInputs.insert(make_pair(axisName, FAxisInput(lowKeys, highKeys)));
}

void CInputManager::AddAction(tstring actionName, int actionKey)
{
}

void CInputManager::AddAction(tstring actionName, vector<int> actionKeys)
{
}

void CInputManager::UpdateInputValue()
{
	// 축 입력 값 갱신
	for (auto iter = AxisInputs.begin(); iter != AxisInputs.end(); ++iter)
		iter->second.UpdateInputAxisValue();
}

float CInputManager::GetAxis(tstring axisName)
{
	return Instance()->AxisInputs[axisName].AxisValue;
}

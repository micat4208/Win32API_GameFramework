#pragma once

#include "Include/DefaultInclude.h"
#include "Struct/Vector/Vector.h"

interface IUIComponent
{
	USE_INTERFACE(IUIComponent);

	virtual void SetUIObject(class CUIObject* uiObject) PURE;
	virtual class CUIObject* GetUIObject() const PURE;
	virtual FVector GetAnchor() const PURE;
};
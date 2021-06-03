#include "ScreenObject.h"

#include "Base/GameObject/UIObject/UIObject.h"

void CScreenObject::DestroyUIObject(CUIObject* uiObject)
{
	auto iter = UIObjects.begin();

	for (; iter != UIObjects.end(); ++iter)
		if (*iter == uiObject) break;

	OwnerScene->Destroy(uiObject);
	*iter = nullptr;
}

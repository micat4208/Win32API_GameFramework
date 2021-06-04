#include "ScreenObject.h"

#include "Base/GameObject/UIObject/UIObject.h"

void CScreenObject::DestroyUIObject(CUIObject* uiObject)
{
	UIObjects.remove(uiObject);
	OwnerScene->Destroy(uiObject);
}

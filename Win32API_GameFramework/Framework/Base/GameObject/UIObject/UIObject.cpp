#include "UIObject.h"

#include "Interface/UIComponent.h"

#include "Base/GameObject/ScreenObject/ScreenObject.h"

#include "Base/Scene/Scene.h"
#include "Bitmap/Bitmap.h"

void CUIObject::Initialize()
{
	Super::Initialize();

	ScreenObject = nullptr;
	Anchor = (Pivot = FVector::OneVector()) * 0.5f;
}

void CUIObject::OnUIObjectCreated()
{
	// UIObject 의 Boundary 갱신합니다.
	UpdateUIObjectBoundary();

	for (auto uiComponent : UIComponents)
		uiComponent->UpdateUIComponentBoundary();

}

void CUIObject::UpdateUIObjectBoundary()
{
	if (!ScreenObject) return;

	const FRect& screenBounds = ScreenObject->GetScreenBounds();

	// UIObject 의 Anchor 로 지정된 위치를 얻습니다.
	FVector uiObjectAnchorPosition = screenBounds.Min +
		(screenBounds.GetSize() * GetAnchor());

	// UIObject 의 좌측 상단 위치
	FVector uiObjectLT = uiObjectAnchorPosition + Position -
		(GetSize() * GetPivot());

	// UIObject 바운더리를 갱신합니다.
	Bounds = FRect(uiObjectLT, uiObjectLT + GetSize());
}

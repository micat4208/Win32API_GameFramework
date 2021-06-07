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
	// UIObject �� Boundary �����մϴ�.
	UpdateUIObjectBoundary();

	for (auto uiComponent : UIComponents)
		uiComponent->UpdateUIComponentBoundary();

}

void CUIObject::UpdateUIObjectBoundary()
{
	if (!ScreenObject) return;

	const FRect& screenBounds = ScreenObject->GetScreenBounds();

	// UIObject �� Anchor �� ������ ��ġ�� ����ϴ�.
	FVector uiObjectAnchorPosition = screenBounds.Min +
		(screenBounds.GetSize() * GetAnchor());

	// UIObject �� ���� ��� ��ġ
	FVector uiObjectLT = uiObjectAnchorPosition + Position -
		(GetSize() * GetPivot());

	// UIObject �ٿ������ �����մϴ�.
	Bounds = FRect(uiObjectLT, uiObjectLT + GetSize());
}

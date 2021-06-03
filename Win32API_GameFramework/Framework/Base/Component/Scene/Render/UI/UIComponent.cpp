#include "UIComponent.h"

void CUIComponent::Initialize()
{
	super::Initialize();

	Anchor = FVector::OneVector() * 0.5f;
}

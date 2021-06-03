#include "UIObject.h"

void CUIObject::Initialize()
{
	super::Initialize();

	Anchor = (Size = FVector::OneVector()) * 0.5f;
}

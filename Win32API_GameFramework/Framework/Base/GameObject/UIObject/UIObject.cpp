#include "UIObject.h"

#include "Interface/UIComponent.h"

#include "Base/Scene/Scene.h"
#include "Bitmap/Bitmap.h"

void CUIObject::Initialize()
{
	Super::Initialize();

	Anchor = (Size = FVector::OneVector()) * 0.5f;
}

void CUIObject::Tick(float dt)
{
	Super::Tick(dt);

	FVector lt(
		Position.X - (Size.X * Anchor.X),
		Position.Y - (Size.Y * Anchor.Y));


}

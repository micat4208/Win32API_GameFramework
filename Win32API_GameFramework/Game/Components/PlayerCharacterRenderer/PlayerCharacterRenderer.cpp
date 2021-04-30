#include "PlayerCharacterRenderer.h"

#include "Framework/Base/GameObject/GameObject.h"

void CPlayerCharacterRenderer::Render(HDC hdc)
{
	super::Render(hdc);

	float left		= Owner->Position.X - 50.0f;
	float top		= Owner->Position.Y - 50.0f;
	float right		= Owner->Position.X + 50.0f;
	float bottom	= Owner->Position.Y + 50.0f;

	Ellipse(hdc, left, top, right, bottom);


}

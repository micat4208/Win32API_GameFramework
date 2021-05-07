#include "DebugDrawInfo.h"
#include "Framework/Statics/GameplayStatics.h"

void FDebugDrawInfo::Initialize()
{
	super::Initialize();
	HBrush = HPen = NULL;
}

void FDebugDrawInfo::Release()
{
	super::Release();

	if (HBrush)
	{
		::DeleteObject(HBrush);
		HBrush = NULL;
	}

	if (HPen)
	{
		::DeleteObject(HPen);
		HPen = NULL;
	}
}

void FDebugDrawInfo::InitializeDebugDrawInfo(
	EDebugDrawType debugDrawType, 
	FVector vec1, 
	FVector vec2,
	COLORREF color, 
	float duration)
{
	DebugDrawType = debugDrawType;
	Vec1 = vec1;
	Vec2 = vec2;
	Color = color;
	DrawStartTime = CGameplayStatics::GetTime();
	Duration = duration;


	switch (DebugDrawType)
	{
	case EDebugDrawType::DT_Rect:
		HBrush = CreateSolidBrush(Color);
		HPen = CreatePen(PS_SOLID, 1, Color);
		FnDraw = [this](HDC hdc)
		{
			Rectangle(hdc,
				Vec1.X - (Vec2.X * 0.5f),
				Vec1.Y - (Vec2.Y * 0.5f),
				Vec1.X + (Vec2.X * 0.5f),
				Vec1.Y + (Vec2.Y * 0.5f));
		};

		break;

	case EDebugDrawType::DT_Circle:
		HBrush = CreateSolidBrush(Color);
		HPen = CreatePen(PS_SOLID, 1, Color);
		FnDraw = [this](HDC hdc)
		{
			Ellipse(hdc,
				Vec1.X - (Vec2.X * 0.5f),
				Vec1.Y - (Vec2.Y * 0.5f),
				Vec1.X + (Vec2.X * 0.5f),
				Vec1.Y + (Vec2.Y * 0.5f));
		};
		break;

	case EDebugDrawType::DT_LINE:
		HPen = CreatePen(PS_SOLID, 1, Color);
		FnDraw = [this](HDC hdc)
		{
			MoveToEx(hdc, Vec1.X, Vec1.Y, NULL);
			LineTo(hdc, Vec2.X, Vec2.Y);
		};
		break;
	}
}

void FDebugDrawInfo::Draw(HDC hdc) const
{
	HGDIOBJ oldBrush = NULL;
	HGDIOBJ oldPen = NULL;

	if (HBrush != NULL) oldBrush	= SelectObject(hdc, HBrush);
	if (HPen != NULL)	oldPen		= SelectObject(hdc, HPen);

	FnDraw(hdc);

	if (HBrush != NULL) SelectObject(hdc, oldBrush);
	if (HPen != NULL)	SelectObject(hdc, oldPen);
}
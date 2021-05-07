#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Enum/DebugDrawType.h"
#include "Framework/Struct/Vector/Vector.h"

struct FDebugDrawInfo final : 
	public CObject
{
public :
	// 그릴 도형을 나타냅니다.
	EDebugDrawType DebugDrawType;

	// 사각형이나 원의 중심 위치, 선의 시작 지점을 나타냅니다.
	FVector Vec1;

	//  사각형이나 원의 너비 / 높이, 선의 끝 지점을 나타냅니다.
	FVector Vec2;

	// 그리기 시작한 시간
	float DrawStartTime;

	// 그릴 시간
	float Duration;

	// 그리기 색상
	COLORREF Color;

	HGDIOBJ HBrush;
	HGDIOBJ HPen;

	function<void(HDC)> FnDraw;

public :
	virtual void Initialize() override;
	virtual void Release() override;

	void InitializeDebugDrawInfo(
		EDebugDrawType debugDrawType, 
		FVector vec1, 
		FVector vec2, 
		COLORREF color,
		float duration = 5.0f);

	void Draw(HDC hdc) const;

};
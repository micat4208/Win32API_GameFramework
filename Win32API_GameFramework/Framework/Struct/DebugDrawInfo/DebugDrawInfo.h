#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Enum/DebugDrawType.h"
#include "Framework/Struct/Vector/Vector.h"

struct FDebugDrawInfo final : 
	public CObject
{
public :
	// �׸� ������ ��Ÿ���ϴ�.
	EDebugDrawType DebugDrawType;

	// �簢���̳� ���� �߽� ��ġ, ���� ���� ������ ��Ÿ���ϴ�.
	FVector Vec1;

	//  �簢���̳� ���� �ʺ� / ����, ���� �� ������ ��Ÿ���ϴ�.
	FVector Vec2;

	// �׸��� ������ �ð�
	float DrawStartTime;

	// �׸� �ð�
	float Duration;

	// �׸��� ����
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
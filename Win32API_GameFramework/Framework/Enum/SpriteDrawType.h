#pragma once
#include "Include/TypeDefine.h"

enum class ESpriteDrawType : uint8
{
	Hide,				// �̹����� �׸��� �ʽ��ϴ�.
	UseTransparentBlt,	// TransparentBlt �� ����մϴ�.
	UseStretchBlt		// StretchBlt �� ����մϴ�.
};
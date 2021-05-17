#pragma once
#include "Include/TypeDefine.h"

enum class ESpriteDrawType : uint8
{
	Hide,				// 이미지를 그리지 않습니다.
	UseTransparentBlt,	// TransparentBlt 을 사용합니다.
	UseStretchBlt		// StretchBlt 을 사용합니다.
};
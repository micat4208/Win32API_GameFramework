#include "BitmapInfo.h"

FBitmapInfo::FBitmapInfo()
{
	PixelColors = nullptr;
	PixelXCount = 0;
	PixelYCount = 0;
}

void FBitmapInfo::InitializeBitmapInfo(
	COLORREF** pixelColors,
	int32 pixelXCount,
	int32 pixelYCount)
{
	PixelColors = pixelColors;
	PixelXCount = pixelXCount;
	PixelYCount = pixelYCount;
}

void FBitmapInfo::Release()
{
	if (PixelColors)
	{
		// 색상 정보 배열 해제
		for (int32 y = 0; y < PixelYCount; ++y)
			delete[] PixelColors[y];
		delete[] PixelColors;

		PixelColors = nullptr;
		PixelXCount = 0;
		PixelYCount = 0;
	}

	super::Release();
}

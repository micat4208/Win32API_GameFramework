#pragma once
#include "Framework/Base/Object/Object.h"

// 비트맵 정보를 나타냅니다.
struct FBitmapInfo :
    public CObject
{
public :
    // 비트맵의 색상 정보를 갖는 배열
    COLORREF** PixelColors;

    // 픽셀 개수를 나타냅니다.
    int32 PixelXCount;
    int32 PixelYCount;

public :
    FBitmapInfo();

public :
    void InitializeBitmapInfo(COLORREF** pixelColors, int32 pixelXCount, int32 pixelYCount);

public :
    virtual void Release() override;

};


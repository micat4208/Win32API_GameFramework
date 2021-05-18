#pragma once
#include "Framework/Base/Object/Object.h"

// ��Ʈ�� ������ ��Ÿ���ϴ�.
struct FBitmapInfo :
    public CObject
{
public :
    // ��Ʈ���� ���� ������ ���� �迭
    COLORREF** PixelColors;

    // �ȼ� ������ ��Ÿ���ϴ�.
    int32 PixelXCount;
    int32 PixelYCount;

public :
    FBitmapInfo();

public :
    void InitializeBitmapInfo(COLORREF** pixelColors, int32 pixelXCount, int32 pixelYCount);

public :
    virtual void Release() override;

};


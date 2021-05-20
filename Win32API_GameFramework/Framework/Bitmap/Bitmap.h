#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Struct/Vector/Vector.h"
#include "Framework/Struct/BitmapInfo/BitmapInfo.h"

class CBitmap final :
    public CObject
{
private :
    HDC Hdc, MemDC,
        XFlippedHDC, YFlippedHDC, XYFlippedHDC;

    HBITMAP Bmp, OldBmp,
        XFlippedBmp, YFlippedBmp, XYFlippedBmp,
        OldXFlippedBmp, OldYFlippedBmp, OldXYFlippedBmp;

    FVector Size;

    FBitmapInfo* BitmapInfo;

    // ó������ �ø��� Bmp �� �ε��ų �������� ��Ÿ���ϴ�.
    bool bUseFlippedBmp;

public :
    // Flip ���¸� ��Ÿ���ϴ�.
    bool bIsFlippedX, bIsFlippedY;




public :
    CBitmap();

public :
    // ��Ʈ�� �̹����� �ε��մϴ�.
    static CBitmap* LoadBmp(CBitmap* bitmap, tstring path, bool bUseFlippedBmp = true);

public :
    virtual void Release() override;

public :
    // �̹����� �������ϴ�.
    /// - flipX �� true ��� ���η� �������ϴ�.
    /// - flipY �� true ��� ���η� �������ϴ�.
    void FlipXY(bool flipX, bool flipY);

    FORCEINLINE FVector GetSize() const
    { return Size; }

    FORCEINLINE HDC GetDC() const
    {
        if (!bUseFlippedBmp)                    return MemDC;

        if (bIsFlippedX && bIsFlippedY)         return XYFlippedHDC;
        else if (!bIsFlippedX && !bIsFlippedY)  return MemDC;

        if (bIsFlippedX)                        return XFlippedHDC;
        else                                    return YFlippedHDC;
    }

    FORCEINLINE bool IsValid() const
    { return Bmp != NULL; }
};


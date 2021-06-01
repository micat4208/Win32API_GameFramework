#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Struct/Vector/Vector.h"
#include "Framework/Struct/BitmapInfo/BitmapInfo.h"

class CBitmap final :
    public CObject
{
private:
    static map<tstring, CBitmap*> LoadedBitmaps;

private :
    HDC Hdc, MemDC,
        XFlippedHDC, YFlippedHDC, XYFlippedHDC;

    HBITMAP Bmp, OldBmp,
        XFlippedBmp, YFlippedBmp, XYFlippedBmp,
        OldXFlippedBmp, OldYFlippedBmp, OldXYFlippedBmp;

    FVector Size;

    FBitmapInfo* BitmapInfo;

    // 처음부터 플립된 Bmp 를 로드시킬 것인지를 나타냅니다.
    bool bUseFlippedBmp;

public :
    // Flip 상태를 나타냅니다.
    bool bIsFlippedX, bIsFlippedY;


public :
    CBitmap();

public :
    // 비트맵 이미지를 로드합니다.
    static CBitmap* LoadBmp(CBitmap* bitmap, tstring path, bool bUseFlippedBmp = true, tstring key = TEXT("USE_PATH"));

public :
    static void ReleaseAllBmp();
    virtual void Release() override;

public :
    // 이미지를 뒤집습니다.
    /// - flipX 가 true 라면 가로로 뒤집습니다.
    /// - flipY 가 true 라면 세로로 뒤집습니다.
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


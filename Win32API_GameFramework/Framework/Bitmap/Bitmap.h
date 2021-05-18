#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Struct/Vector/Vector.h"
#include "Framework/Struct/BitmapInfo/BitmapInfo.h"

class CBitmap final :
    public CObject
{
private :
    HDC Hdc, MemDC;
    HBITMAP Bmp, OldBmp;
    FVector Size;

    FBitmapInfo* BitmapInfo;


public :
    CBitmap();

public :
    // 비트맵 이미지를 로드합니다.
    static CBitmap* LoadBmp(CBitmap* bitmap, tstring path);

public :
    virtual void Release() override;

public :
    // 이미지를 뒤집습니다.
    /// - flipX 가 true 라면 가로로 뒤집습니다.
    /// - flipY 가 true 라면 세로로 뒤집습니다.
    void FlipXY(bool flipX, bool flipY);

    FORCEINLINE FVector GetSize() const
    { return Size; }

    FORCEINLINE HDC GetDC() const
    { return MemDC; }

    FORCEINLINE bool IsValid() const
    { return Bmp != NULL; }
};


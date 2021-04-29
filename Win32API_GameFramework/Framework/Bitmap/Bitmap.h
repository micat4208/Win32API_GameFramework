#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Struct/Vector/Vector.h"

class CBitmap final :
    public CObject
{
private :
    HDC Hdc, MemDC;
    HBITMAP Bmp, OldBmp;
    FVector Size;

public :
    CBitmap();

public :
    // 비트맵 이미지를 로드합니다.
    static CBitmap* LoadBmp(CBitmap*& bitmap, tstring path);

public :
    virtual void Release() override;

public :
    FORCEINLINE FVector GetSize() const
    { return Size; }

    FORCEINLINE HDC GetDC() const
    { return MemDC; }
};


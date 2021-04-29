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
    // ��Ʈ�� �̹����� �ε��մϴ�.
    static CBitmap* LoadBmp(CBitmap*& bitmap, tstring path);

public :
    virtual void Release() override;

public :
    FORCEINLINE FVector GetSize() const
    { return Size; }

    FORCEINLINE HDC GetDC() const
    { return MemDC; }
};


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
    // ��Ʈ�� �̹����� �ε��մϴ�.
    static CBitmap* LoadBmp(CBitmap* bitmap, tstring path);

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
    { return MemDC; }

    FORCEINLINE bool IsValid() const
    { return Bmp != NULL; }
};


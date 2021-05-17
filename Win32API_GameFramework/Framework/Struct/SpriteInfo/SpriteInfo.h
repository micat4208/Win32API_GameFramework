#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Struct/Vector/Vector.h"
#include "Framework/Enum/SpriteDrawType.h"

#ifndef USE_LOADED_SIZE
#define USE_LOADED_SIZE FVector(-1.0f, -1.0f)
#endif


// ��������Ʈ ������ ��Ÿ���ϴ�.
struct FSpriteInfo :
    public CObject
{
private :
    // �ε�� �̹����� ��Ÿ���ϴ�.
    class CBitmap* LoadedBitmap;

    // �ε�� ��������Ʈ �̹����� ���� ���� ũ�⸦ ��Ÿ���ϴ�.
    /// - �� ���� �̹��� �ε� �� �ڵ����� �����˴ϴ�.
    FVector LoadedSpriteImageSize;

public :
    // ��������Ʈ �̹��� �׸��� ���
    ESpriteDrawType SpriteDrawType;

    // SpriteDrawType �� UseTransparentBlt �� ��� ���� ������ ��Ÿ���ϴ�.
    COLORREF CRTransparent;

    // SpeiteDrawType �� UseStretchBlt �� ��� �׸��� ����� ��Ÿ���ϴ�.
    DWORD DWRop;

    // ��������Ʈ �̹��� ���� ��� �е�
    /// - �̹��� �ڸ��� ���� ��ġ�� ��Ÿ���ϴ�.
    FVector CropLT;

    // ��������Ʈ �̹��� ���� ���� ũ�⸦ ��Ÿ���ϴ�.
    /// - �ε�� �̹��� ũ�⿡�� CropLT ���� �����Ų ũ���̸� �̹����� �׸� �� ���˴ϴ�.
    /// - �׻� LoadedSpriteImageSize ���� �۰ų� ���ƾ� �մϴ�.
    FVector SpriteImageSize;

    // �׷����� ��������Ʈ �̹����� �������� ��Ÿ���ϴ�.
    /// - �⺻ ���� �߾�(0.5f, 0.5f) �Դϴ�.
    /// - (0, 0) : ���� ���
    /// - (1, 1) : ���� �ϴ�
    FVector DrawPivot;

public :
    FSpriteInfo();

    void InitializeSpriteInfo(
        tstring imagePath,
        ESpriteDrawType spriteDrawType,
        FVector imageSize = USE_LOADED_SIZE);

public :
    virtual void Release() override;

public :
    HDC GetDC() const;

    FORCEINLINE FVector GetLoadedSpriteImageSize() const
    { return LoadedSpriteImageSize; }

    bool IsValid() const;

};


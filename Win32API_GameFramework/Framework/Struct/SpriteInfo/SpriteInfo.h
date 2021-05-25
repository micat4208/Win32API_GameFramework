#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Struct/Vector/Vector.h"
#include "Framework/Enum/SpriteDrawType.h"

#ifndef USE_LOADED_SIZE
#define USE_LOADED_SIZE FVector(-1.0f, -1.0f)
#endif


// 스프라이트 정보를 나타냅니다.
struct FSpriteInfo :
    public CObject
{
private :
    // 로드된 이미지를 나타냅니다.
    class CBitmap* LoadedBitmap;

    // 로드된 스프라이트 이미지의 가로 세로 크기를 나타냅니다.
    /// - 이 값은 이미지 로드 후 자동으로 설정됩니다.
    FVector LoadedSpriteImageSize;

public :
    // 스프라이트 이미지 그리기 방식
    ESpriteDrawType SpriteDrawType;

    // SpriteDrawType 이 UseTransparentBlt 일 경우 숨길 색상을 나타냅니다.
    COLORREF CRTransparent;

    // SpeiteDrawType 이 UseStretchBlt 일 경우 그리기 방식을 나타냅니다.
    DWORD DWRop;

    // 스프라이트 이미지 좌측 상단 패딩
    /// - 이미지 자르기 시작 위치를 나타냅니다.
    FVector CropLT;

    // 스프라이트 이미지 가로 세로 크기를 나타냅니다.
    /// - 로드된 이미지 크기에서 CropLT 값을 적용시킨 크기이며 이미지를 그릴 때 사용됩니다.
    /// - 항상 LoadedSpriteImageSize 보다 작거나 같아야 합니다.
    FVector SpriteImageSize;

    // 그려지는 스프라이트 이미지의 기준점을 나타냅니다.
    /// - 기본 값은 중앙(0.5f, 0.5f) 입니다.
    /// - (0, 0) : 좌측 상단
    /// - (1, 1) : 우측 하단
    FVector DrawPivot;

public :
    FSpriteInfo();

    void InitializeSpriteInfo(
        tstring imagePath,
        ESpriteDrawType spriteDrawType,
        FVector imageSize = USE_LOADED_SIZE,
        bool bUseFlip = true);

public :
    virtual void Release() override;

public :
    // 여러개의 SpriteInfo 를 생성합니다.
    /// - outSpriteInfos : 생성된 SpriteInfo 들을 저장할 vector 을 전달합니다.
    /// - imagePaths : 이미지 경로들을 전달합니다.
    /// - spriteDrawType : 스프라이트 이미지 그리기 방식을 전달합니다.
    /// - pivot : 이미지 피벗을 전달합니다.
    /// - crTransparent : spriteDrawType 에 UseTransparentBlt 이 전달될 경우, 숨길 색상을 전달합니다.
    /// - dwRop : spriteDrawType 에 UseStretchBlt 이 전달될 경우, 그리기 방식을 전달합니다.
    static void MakeSpriteInfos(
        vector<FSpriteInfo*>& outSpriteInfos,
        const vector<tstring>& imagePaths,
        ESpriteDrawType spriteDrawType,
        FVector pivot = FVector(0.5f, 0.5f),
        COLORREF crTransparent = RGB(255, 0, 255),
        DWORD dwRop = SRCCOPY);

public :
    HDC GetDC() const;

    FORCEINLINE FVector GetLoadedSpriteImageSize() const
    { return LoadedSpriteImageSize; }

    FORCEINLINE class CBitmap* GetLoadedBitmap() const
    { return LoadedBitmap; }

    bool IsValid() const;

};


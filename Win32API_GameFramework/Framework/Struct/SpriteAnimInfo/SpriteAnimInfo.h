#pragma once

#include "Framework/Base/Object/Object.h"

#include "Framework/Struct/SpriteInfo/SpriteInfo.h"

// 하나의 스프라이트 애니메이션 정보를 나타내는 구조체입니다.
class FSpriteAnimInfo :
    public CObject
{
public :
    // 애니메이션을 표현하기 위해 사용되는 SpriteInfo 들을 나타냅니다.
    vector<FSpriteInfo*> SpriteInfos;

    // 스프라이트 전환 딜레이
    float SpriteDelay;

public :
    FSpriteAnimInfo();

public :
    void InitializeSpriteAnimInfo(const vector<FSpriteInfo*> spriteInfos, float spriteDelay);

    virtual void Release() override;

public :
    FORCEINLINE FSpriteInfo* operator[](int32 index) const
    { return (SpriteInfos.size() == 0) ? nullptr : *(SpriteInfos.begin() + index); }

    // 마지막 스프라이트 인덱스를 반환합니다.
    FORCEINLINE int32 GetLastSpriteIndex() const
    { return SpriteInfos.size() - 1; }

};


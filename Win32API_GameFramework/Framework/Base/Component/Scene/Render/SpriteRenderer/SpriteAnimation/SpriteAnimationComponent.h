#pragma once
#include "Framework/Base/Component/Scene/Render/SpriteRenderer/SpriteRendererComponent.h"
#include "Framework/Struct/SpriteAnimInfo/SpriteAnimInfo.h"

#ifndef STOP_ANIMATION
#define STOP_ANIMATION      TEXT("NONE")
#endif

class CSpriteAnimationComponent :
    public CSpriteRendererComponent
{
private :
    // 현재 재생중인 애니메이션 이름을 나타냅니다.
    tstring SpriteAnimationName;

    // 스프라이트 애니메이션 정보들이 저장됩니다.
    map<tstring, FSpriteAnimInfo*> SpriteAnimInfos;

    // 현재 재생중인 애니메이션 정보를 나타냅니다.
    FSpriteAnimInfo* SpriteAnimation;

    // 스프라이트 인덱스
    int32 SpriteIndex;

    // 마지막으로 스프라이트를 전환한 시간을 나타냅니다.
    float LastSpriteChangedTime;

public :
    virtual void Initialize() override;
    virtual void Tick(float dt) override;
    virtual void Release() override;

    virtual void FlipXY(bool flipX, bool flipY) override;

private :
    void LoopAnimation();

public :
    // 스프라이트 애니메이션을 추가합니다.
    /// - newAnimationName : 추가할 애니메이션의 이름을 전달합니다.
    /// - spriteInfos : 애니메이션에서 사용되는 Sprite 정보를 갖는 배열을 전달합니다.
    /// - spriteDelay : 스프라이트 전환 시간을 전달합니다.
    void AddSpriteAnimation(
        tstring newAnimationName,
        const vector<FSpriteInfo*>& spriteInfos,
        float spriteDelay);

    ///  SpriteAnimation 을 재생시킵니다.
    /// - animationName : 재생시킬 애니메이션 이름을 전달합니다.
    ///   - 애니메이션 표시를 중지시키려면 STOP_ANIMATION 을 전달해야 합니다.
    /// - startIndex : 재생시킬 애니메이션 인덱스를 전달합니다.
    void PlaySpriteAnimation(tstring animationName, int32 startIndex = 0);


};


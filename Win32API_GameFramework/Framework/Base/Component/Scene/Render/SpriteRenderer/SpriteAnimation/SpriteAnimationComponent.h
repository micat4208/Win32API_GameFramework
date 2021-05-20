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
    // ���� ������� �ִϸ��̼� �̸��� ��Ÿ���ϴ�.
    tstring SpriteAnimationName;

    // ��������Ʈ �ִϸ��̼� �������� ����˴ϴ�.
    map<tstring, FSpriteAnimInfo*> SpriteAnimInfos;

    // ���� ������� �ִϸ��̼� ������ ��Ÿ���ϴ�.
    FSpriteAnimInfo* SpriteAnimation;

    // ��������Ʈ �ε���
    int32 SpriteIndex;

public :
    virtual void Initialize() override;
    virtual void Release() override;

public :
    // ��������Ʈ �ִϸ��̼��� �߰��մϴ�.
    /// - newAnimationName : �߰��� �ִϸ��̼��� �̸��� �����մϴ�.
    /// - spriteInfos : �ִϸ��̼ǿ��� ���Ǵ� Sprite ������ ���� �迭�� �����մϴ�.
    /// - spriteDelay : ��������Ʈ ��ȯ �ð��� �����մϴ�.
    void AddSpriteAnimation(
        tstring newAnimationName,
        const vector<FSpriteInfo*>& spriteInfos,
        float spriteDelay);

    ///  SpriteAnimation �� �����ŵ�ϴ�.
    /// - animationName : �����ų �ִϸ��̼� �̸��� �����մϴ�.
    ///   - �ִϸ��̼� ǥ�ø� ������Ű���� STOP_ANIMATION �� �����ؾ� �մϴ�.
    /// - startIndex : �����ų �ִϸ��̼� �ε����� �����մϴ�.
    void PlaySpriteAnimation(tstring animationName, int32 startIndex = 0);


};


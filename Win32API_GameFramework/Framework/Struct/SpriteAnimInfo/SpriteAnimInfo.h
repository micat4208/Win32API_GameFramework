#pragma once

#include "Framework/Base/Object/Object.h"

#include "Framework/Struct/SpriteInfo/SpriteInfo.h"

// �ϳ��� ��������Ʈ �ִϸ��̼� ������ ��Ÿ���� ����ü�Դϴ�.
class FSpriteAnimInfo :
    public CObject
{
public :
    // �ִϸ��̼��� ǥ���ϱ� ���� ���Ǵ� SpriteInfo ���� ��Ÿ���ϴ�.
    vector<FSpriteInfo*> SpriteInfos;

    // ��������Ʈ ��ȯ ������
    float SpriteDelay;

public :
    FSpriteAnimInfo();

public :
    void InitializeSpriteAnimInfo(const vector<FSpriteInfo*> spriteInfos, float spriteDelay);

    virtual void Release() override;

public :
    FORCEINLINE FSpriteInfo* operator[](int32 index) const
    { return (SpriteInfos.size() == 0) ? nullptr : *(SpriteInfos.begin() + index); }

    // ������ ��������Ʈ �ε����� ��ȯ�մϴ�.
    FORCEINLINE int32 GetLastSpriteIndex() const
    { return SpriteInfos.size() - 1; }

};


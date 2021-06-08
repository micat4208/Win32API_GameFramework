#pragma once
#include "Base/GameObject/UIObject/UIObject.h"

CLASS(CPlayerHUD, CUIObject)
class CPlayerHUD :
    public CUIObject
{
    USE_CLASS(CPlayerHUD);

private :
    class CUISpriteRendererComponent* HpBackground;
    class CUISpriteRendererComponent* HpForeground;
    class CUISpriteRendererComponent* HpIcon;

public :
    virtual void Initialize() override;

public :
    // Hp 수치를 설정합니다.
    void SetHp(float hp);

};


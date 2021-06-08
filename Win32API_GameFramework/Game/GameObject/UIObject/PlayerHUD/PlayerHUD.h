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
    // Hp ��ġ�� �����մϴ�.
    void SetHp(float hp);

};


#pragma once
#include "Base/GameObject/GameObject.h"

CLASS(CUIObject, CGameObject)
class CUIObject :
    public CGameObject
{
    USE_CLASS(CUIObject);

protected :
    list<interface IUIComponent*> UIComponents;

    FVector Size;
    FVector Anchor;
    FVector Pivot;

public :
    virtual void Initialize() override;
    virtual void Tick(float dt) override;

    // UIObject 의 화면상 위치를 얻습니다.
    FORCEINLINE FVector GetUIPosition() const
    {  return Position + FVector(WND_WIDTH * Anchor.X, WND_HEIGHT * Anchor.Y); }

    // UIObject 의 바운더리를 얻습니다.
    FORCEINLINE FRect GetBounds() const
    {
        FVector lt = GetUIPosition() - FVector(Size.X * Pivot.X, Size.Y * Pivot.Y);
        return FRect(lt, lt + Size);
    }
};


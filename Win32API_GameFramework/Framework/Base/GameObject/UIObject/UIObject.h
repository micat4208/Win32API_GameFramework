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

    // UIObject �� ȭ��� ��ġ�� ����ϴ�.
    FORCEINLINE FVector GetUIPosition() const
    {  return Position + FVector(WND_WIDTH * Anchor.X, WND_HEIGHT * Anchor.Y); }

    // UIObject �� �ٿ������ ����ϴ�.
    FORCEINLINE FRect GetBounds() const
    {
        FVector lt = GetUIPosition() - FVector(Size.X * Pivot.X, Size.Y * Pivot.Y);
        return FRect(lt, lt + Size);
    }
};


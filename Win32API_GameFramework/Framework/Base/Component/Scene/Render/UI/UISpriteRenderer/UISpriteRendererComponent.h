#pragma once
#include "Base/Component/Scene/Render/SpriteRenderer/SpriteRendererComponent.h"
#include "Struct/Rect/Rect.h"
#include "Interface/UIComponent.h"

CLASS(CUISpriteRendererComponent, CSpriteRendererComponent)
class CUISpriteRendererComponent :
    public CSpriteRendererComponent,
    public IUIComponent
{
    USE_CLASS(CUISpriteRendererComponent);

private :
    class CUIObject* UIObject;
    FVector Anchor;

public :
    FRect Bounds;
    FVector Pivot;
    FVector Anchor;

public :
    CUISpriteRendererComponent();


    virtual void UpdateUIComponentBoundary() override;

    FORCEINLINE virtual void SetPivot(FVector newPivot)
    {
        Pivot = newPivot;
        UpdateUIComponentBoundary();
    }
    FORCEINLINE virtual FVector GetPivot() const
    { return Pivot; }

    FORCEINLINE virtual void SetAnchor(FVector newAnchor)
    {
        Anchor = newAnchor;
        UpdateUIComponentBoundary();
    }
    FORCEINLINE virtual FVector GetAnchor() const override
    { return Anchor; }

    FORCEINLINE virtual FRect GetBounds() const
    { return Bounds; }

    FORCEINLINE virtual FVector GetComponentPosition() const override
    { return Bounds.GetCenter(); }

    FORCEINLINE virtual FVector ToRenderPosition(const FVector& scenePosition) const final override
    { return Bounds.Min; }

    FORCEINLINE virtual void SetDrawSpriteInfo(FSpriteInfo* newSpriteInfo) override
    {
        Super::SetDrawSpriteInfo(newSpriteInfo);

        if (newSpriteInfo)
            UpdateUIComponentBoundary();
    }

};


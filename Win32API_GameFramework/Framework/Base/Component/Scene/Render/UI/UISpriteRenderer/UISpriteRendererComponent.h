#pragma once
#include "Base/Component/Scene/Render/SpriteRenderer/SpriteRendererComponent.h"
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
    CUISpriteRendererComponent();

    FORCEINLINE virtual void SetUIObject(class CUIObject* uiObject) override
    { UIObject = uiObject; }

    FORCEINLINE virtual class CUIObject* GetUIObject() const override
    { return UIObject; }

    FORCEINLINE virtual FVector GetAnchor() const override
    { return Anchor; }

    virtual FVector GetComponentPosition() const override;

};


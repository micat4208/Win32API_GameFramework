#include "UISpriteRendererComponent.h"
#include "Base/GameObject/UIObject/UIObject.h"

CUISpriteRendererComponent::CUISpriteRendererComponent()
{
	UIObject = nullptr;
}

FVector CUISpriteRendererComponent::GetComponentPosition() const
{
	if (!GetUIObject()) return FVector::ZeroVector();
	else
	{
		FRect uiObjectBounds = GetUIObject()->GetBounds();
		FVector uiObjectSize = uiObjectBounds.GetSize();

		// TODO UISpriteRenderer ��ġ ���ϱ�
		/// (Anchor ����)
	}
}

#include "RenderComponent.h"

#include "Framework/Base/GameObject/GameObject.h"
#include "Framework/Base/Scene/Scene.h"

CRenderComponent::CRenderComponent()
{
	bUseRender = true;
	SortingOrder = 0;
}

void CRenderComponent::SetSortingOrder(int32 order)
{
	SortingOrder = order;
	Owner->OwnerScene->bNeedSort = true;
}

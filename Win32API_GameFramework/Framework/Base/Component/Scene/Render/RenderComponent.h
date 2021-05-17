#pragma once
#include "Framework/Base/Component/Scene/SceneComponent.h"

// 그리기 기능을 제공하는 컴포넌트
class CRenderComponent abstract :
    public CSceneComponent
{
public :
    // Render 메서드 호출 여부를 나타냅니다.
    bool bUseRender;

private :
    // 그리기 순서를 나타냅니다.
    int32 SortingOrder;

public :
    CRenderComponent();

public :
    // 그리기 동작을 이 곳에 작성합니다.
    virtual void Render(HDC hdc) { }

public :
    void SetSortingOrder(int32 order);

    FORCEINLINE int32 GetSortingOrder() const
    { return SortingOrder; }

    // 활성화중인 씬을 반환합니다.
    class CScene* GetActiveScene() const;

    // 카메라 위치를 적용시킨 위치를 반환합니다.
    FVector ToCameraPosition(const FVector& scenePosition) const;

};


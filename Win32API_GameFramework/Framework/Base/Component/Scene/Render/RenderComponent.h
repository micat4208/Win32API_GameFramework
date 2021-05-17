#pragma once
#include "Framework/Base/Component/Scene/SceneComponent.h"

// �׸��� ����� �����ϴ� ������Ʈ
class CRenderComponent abstract :
    public CSceneComponent
{
public :
    // Render �޼��� ȣ�� ���θ� ��Ÿ���ϴ�.
    bool bUseRender;

private :
    // �׸��� ������ ��Ÿ���ϴ�.
    int32 SortingOrder;

public :
    CRenderComponent();

public :
    // �׸��� ������ �� ���� �ۼ��մϴ�.
    virtual void Render(HDC hdc) { }

public :
    void SetSortingOrder(int32 order);

    FORCEINLINE int32 GetSortingOrder() const
    { return SortingOrder; }

    // Ȱ��ȭ���� ���� ��ȯ�մϴ�.
    class CScene* GetActiveScene() const;

    // ī�޶� ��ġ�� �����Ų ��ġ�� ��ȯ�մϴ�.
    FVector ToCameraPosition(const FVector& scenePosition) const;

};


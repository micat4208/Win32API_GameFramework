#pragma once
#include "Framework/Base/Component/Component.h"

// �׸��� ����� �����ϴ� ������Ʈ
class CRenderComponent abstract :
    public CComponent
{
public :
    // Render �޼��� ȣ�� ���θ� ��Ÿ���ϴ�.
    bool bUseRender;

    // �׸��� ������ ��Ÿ���ϴ�.
    int32 SortingOrder;

public :
    CRenderComponent();

public :
    // �׸��� ������ �� ���� �ۼ��մϴ�.
    virtual void Render(HDC hdc) { }


};


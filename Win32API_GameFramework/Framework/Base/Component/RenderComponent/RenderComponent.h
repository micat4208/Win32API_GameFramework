#pragma once
#include "Framework/Base/Component/Component.h"

// 그리기 기능을 제공하는 컴포넌트
class CRenderComponent abstract :
    public CComponent
{
public :
    // Render 메서드 호출 여부를 나타냅니다.
    bool bUseRender;

public :
    CRenderComponent();

public :
    // 그리기 동작을 이 곳에 작성합니다.
    virtual void Render(HDC hdc) { }


};


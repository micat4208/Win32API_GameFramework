#pragma once
#include "Framework/Base/Component/Component.h"

// GameObject 를 기준으로 특정한 위치, 크기를 갖는 컴포넌트입니다.
class CSceneComponent :
    public CComponent
{
public :
    // 상대 위치를 나타냅니다.
    FVector RelativePosition;

    // 상대 크기를 나타냅니다.
    FVector RelativeScale;

public :
    CSceneComponent();

public :
    // 이 컴포넌트의 월드 위치를 반환합니다.
    FVector GetComponentPosition() const;
};


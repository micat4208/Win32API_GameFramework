#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Struct/Vector/Vector.h"

// 게임 플레이에 필요한 정적 메서드를 제공하는 유틸 클래스
class CGameplayStatics final :
    public CObject
{
public :   
    // 게임 시작 이후 지난 시간을 반환합니다.
    static float GetTime();

    // 마우스 위치를 반환합니다.
    /// - translated : 클라이언트 영역 내의 위치로 변환시켜 반환할 것인지를 결정합니다.
    static FVector GetMousePosition(bool translated = true);

};


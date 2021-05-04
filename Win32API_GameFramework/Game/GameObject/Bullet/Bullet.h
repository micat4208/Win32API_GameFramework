#pragma once
#include "Framework/Base/GameObject/GameObject.h"

class CBullet final:
    public CGameObject
{
private :
    class CMovementComponent* Movement;

    // 총알 게임 오브젝트가 생성된 시간을 나타냅니다.
    float CreatedTime;

    // 총알 게임 오브젝트가 씬에서 살아있을 수 있는 시간
    float MaxLifeTime;

public :
    virtual void Initialize() override;
    virtual void Tick(float dt) override;

public :
    void InitializeBullet();


};


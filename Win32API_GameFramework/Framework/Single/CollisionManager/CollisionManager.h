#pragma once
#include "Framework/Single/ManagerClassBase/ManagerClassBase.h"

class CCollisionManager final :
    public CManagerClassBase<CCollisionManager>
{
private :
    // 충돌 처리를 할 객체들을 나타냅니다.
    list<class CCollisionComponent*> CreatedCollisions;
    list<class CCollisionComponent*> UsedCollisions;
    list<class CCollisionComponent*> DestroyedCollisions;


private : 
    // 원과 원 충돌 검사
    bool DoCollisionTestCircleToCircle(
        class CCollisionComponent* circle1, class CCollisionComponent* circle2);

    // 사각형과 사각형 충돌 검사
    bool DoCollisionTestRectToRect(
        class CCollisionComponent* rect1, class CCollisionComponent* rect2);

    // 원과 사각형 충돌 검사
    bool DoCollisionTestRectToCircle(class CCollisionComponent* rect, class CCollisionComponent* circle);

public :
    void DoCollisionTest();

    void RegisterCollision(class CCollisionComponent* collision);
    void UnRegisterCollision(class CCollisionComponent* collision);

};


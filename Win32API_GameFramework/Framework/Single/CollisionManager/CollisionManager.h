#pragma once
#include "Framework/Single/ManagerClassBase/ManagerClassBase.h"

class CCollisionManager final :
    public CManagerClassBase<CCollisionManager>
{
private :
    // �浹 ó���� �� ��ü���� ��Ÿ���ϴ�.
    list<class CCollisionComponent*> CreatedCollisions;
    list<class CCollisionComponent*> UsedCollisions;
    list<class CCollisionComponent*> DestroyedCollisions;


private : 
    // ���� �� �浹 �˻�
    bool DoCollisionTestCircleToCircle(
        class CCollisionComponent* circle1, class CCollisionComponent* circle2);

    // �簢���� �簢�� �浹 �˻�
    bool DoCollisionTestRectToRect(
        class CCollisionComponent* rect1, class CCollisionComponent* rect2);

    // ���� �簢�� �浹 �˻�
    bool DoCollisionTestRectToCircle(class CCollisionComponent* rect, class CCollisionComponent* circle);

public :
    void DoCollisionTest();

    void RegisterCollision(class CCollisionComponent* collision);
    void UnRegisterCollision(class CCollisionComponent* collision);

};

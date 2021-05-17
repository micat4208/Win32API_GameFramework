#pragma once
#pragma warning (disable : 26812)

#include "Framework/Base/Component/Scene/SceneComponent.h"

#include "Framework/Struct/Rect/Rect.h"

#include "Framework/Enum/CollisionType.h"

// �浹ü�� ��Ÿ���� ���� ������Ʈ
class CCollisionComponent abstract :
    public CSceneComponent
{
protected :
    // �浹ü�� ������ ��Ÿ���ϴ�.
    FRect Bounds;

    // �浹ü Ÿ���� ��Ÿ���ϴ�.
    ECollisionType::Type CollisionType;

public :
    // ��ħ�� �߻����� �� ȣ��˴ϴ�.
    vector< function<void(CCollisionComponent*)> > OverlapEvents;

public :
    // �ٸ� �浹ü�� �������� ��� ȣ��� �޼���
    virtual void OnOverlapped(CCollisionComponent* other);

    virtual void Tick(float dt) override;

protected :
    // Bounds �� �����մϴ�.
    virtual void UpdateBounds() PURE;

public :
    FORCEINLINE const FRect& GetBounds() const
    { return Bounds; }

    FORCEINLINE ECollisionType::Type GetCollisionType() const
    { return CollisionType; }

};

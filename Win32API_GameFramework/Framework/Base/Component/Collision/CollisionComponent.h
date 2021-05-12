#pragma once
#pragma warning (disable : 26812)

#include "Framework/Base/Component/Component.h"

#include "Framework/Struct/Rect/Rect.h"

#include "Framework/Enum/CollisionType.h"

// 충돌체를 나타내기 위한 컴포넌트
class CCollisionComponent abstract :
    public CComponent
{
protected :
    // 충돌체의 영역을 나타냅니다.
    FRect Bounds;

    // 충돌체 타입을 나타냅니다.
    ECollisionType::Type CollisionType;

public :
    // 겹침이 발생했을 때 호출됩니다.
    vector< function<void(CCollisionComponent*)> > OverlapEvents;

public :
    // 다른 충돌체를 감지했을 경우 호출될 메서드
    virtual void OnOverlapped(CCollisionComponent* other);

public :
    FORCEINLINE const FRect& GetBounds() const
    { return Bounds; }

    FORCEINLINE ECollisionType::Type GetCollisionType() const
    { return CollisionType; }

};


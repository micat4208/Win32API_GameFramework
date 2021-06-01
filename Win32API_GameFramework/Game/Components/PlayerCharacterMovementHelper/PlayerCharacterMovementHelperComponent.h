#pragma once
#include "Framework/Base/Component/Component.h"
#include "Framework/Enum/Direction.h"

class CPlayerCharacterMovementHelperComponent final :
    public CComponent
{
private:
    class CPlayerCharacter* PlayerCharacter;
    class CMovementComponent* Movement;

    class CTileMap* TileMap;

    // 플레이어 캐릭터가 바라보는 방향을 나타냄0
    EDirection LookDirection;

    // 타일맵에서 플레이어 캐릭터가 위치하는 타일 위치를 나타냅니다.
    int32 TileMapIndexX;
    int32 TileMapIndexY;

    // 가로 타일 검사 여부를 나타냅니다.
    bool bCheckHorizontalTile;

    // 세로 타일 검사 여부를 나타냅니다.
    bool bCheckVerticalTile;

public:
    CPlayerCharacterMovementHelperComponent();

public:
    virtual void Initialize() override;
    virtual void Start() override;
    virtual void Tick(float dt);

public:
    void SetTileMap(class CTileMap* tileMap);

private:
    // 플레이어 캐릭터가 바라보는 방향을 갱신
    void UpdateLookDirection();

public:
    FORCEINLINE EDirection GetLookDirection() const
    { return LookDirection; }

    // 타일맵에서 플레이어 캐릭터가 위치하는 타일 위치를 갱신합니다.
    void UpdateTileMapIndex();

    // 막힌 타일을 확인합니다.
    void CheckBlockingTile();

};


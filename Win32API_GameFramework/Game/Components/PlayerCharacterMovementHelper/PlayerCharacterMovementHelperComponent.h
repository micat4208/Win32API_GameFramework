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

    // �÷��̾� ĳ���Ͱ� �ٶ󺸴� ������ ��Ÿ��0
    EDirection LookDirection;

    // Ÿ�ϸʿ��� �÷��̾� ĳ���Ͱ� ��ġ�ϴ� Ÿ�� ��ġ�� ��Ÿ���ϴ�.
    int32 TileMapIndexX;
    int32 TileMapIndexY;

    // ���� Ÿ�� �˻� ���θ� ��Ÿ���ϴ�.
    bool bCheckHorizontalTile;

    // ���� Ÿ�� �˻� ���θ� ��Ÿ���ϴ�.
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
    // �÷��̾� ĳ���Ͱ� �ٶ󺸴� ������ ����
    void UpdateLookDirection();

public:
    FORCEINLINE EDirection GetLookDirection() const
    { return LookDirection; }

    // Ÿ�ϸʿ��� �÷��̾� ĳ���Ͱ� ��ġ�ϴ� Ÿ�� ��ġ�� �����մϴ�.
    void UpdateTileMapIndex();

    // ���� Ÿ���� Ȯ���մϴ�.
    void CheckBlockingTile();

};


#pragma once
#include "Framework/Base/Component/Scene/Render/SpriteRenderer/SpriteRendererComponent.h"
class CTileMapRendererComponent :
    public CSpriteRendererComponent
{
public:
    // Ÿ�� �ε���
    int32 TileIndexX;
    int32 TileIndexY;
    bool bIsBlockingTile;

private:
    FSpriteInfo* TileMapSpriteInfo;

public:
    virtual void Initialize() override;
    virtual void Render(HDC hdc) override;
    virtual void Release() override;

public:
    // Ÿ�ϸ� ��ġ�� �����մϴ�.
    void UpdatePosition();

    // �׸��� ���¸� �����մϴ�.
    void UpdateDrawState();
};


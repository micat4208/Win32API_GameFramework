#include "GameScene.h"

#include "Game/GameObject/Character/PlayerCharacter/PlayerCharacter.h"

void CGameScene::Initialize()
{
	super::Initialize();

	LOG(TEXT("CGameScene::Initialize"));

	// �÷��̾� ĳ���͸� �����մϴ�.
	NewGameObject<CPlayerCharacter>(TEXT("PlayerCharacter"));

}

void CGameScene::Tick(float dt)
{
	super::Tick(dt);
}

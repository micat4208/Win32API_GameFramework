#include "GameScene.h"
#include "Game/GameObject/Character/PlayerCharacter/PlayerCharacter.h"

void CGameScene::Initialize()
{
	super::Initialize();

	// �÷��̾� ĳ���͸� �����մϴ�.
	NewGameObject<CPlayerCharacter>(TEXT("PlayerCharacter"));
}

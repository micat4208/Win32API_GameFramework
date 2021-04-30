#include "GameScene.h"

#include "Game/GameObject/Character/PlayerCharacter/PlayerCharacter.h"

void CGameScene::Initialize()
{
	super::Initialize();

	LOG(TEXT("CGameScene::Initialize"));

	// 플레이어 캐릭터를 생성합니다.
	NewGameObject<CPlayerCharacter>(TEXT("PlayerCharacter"));

}

void CGameScene::Tick(float dt)
{
	super::Tick(dt);
}

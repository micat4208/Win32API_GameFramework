#include "GameScene.h"
#include "Game/GameObject/Character/PlayerCharacter/PlayerCharacter.h"

#include "Game/GameObject/TileMap/TileMap.h"
#include "Game/GameObject/Audio/AudioObject.h"

void CGameScene::Initialize()
{
	super::Initialize();

	AudioObject = NewGameObject<CAudioObject>(TEXT("AudioObject"));
	AudioObject->CreateAudio("Resources/Audio/Pleasant_Porridge.mp3");

	TileMap = NewGameObject<CTileMap>(TEXT("TileMap"));
	TileMap->SetTileMap("000000", 3);

	// �÷��̾� ĳ���͸� �����մϴ�.
	NewGameObject<CPlayerCharacter>(TEXT("PlayerCharacter"));
}

#pragma once

/* ~~ ENGINE DEFINES ~~*/
// ���� FPS ����
#define TARGET_FPS		60

// GameInstance Ŭ������ �����մϴ�.
/// - GameInstance Ŭ������ �Ļ� Ŭ������ �����Ѵٸ� �̰��� �����ؾ� �մϴ�.
#define DEF_GAMEINSTANCECLASS CGameInstance

extern class DEF_GAMEINSTANCECLASS* GameInstance;




/* ~~ GAME DEFINE ~~ */
// ó���� ����� �� ����
// - �߰��� Scene Header �� SceneManager.cpp �� �߰��մϴ�.
//#define DEF_SCENE class CScene
#define DEF_SCENE class CGameScene
//#define DEF_SCENE class CMapEditerScene


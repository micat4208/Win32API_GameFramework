#include "PlayerSpriteAnimationComponent.h"

#include "Game/GameObject/Character/PlayerCharacter/PlayerCharacter.h"

#include "Game/Components/Movement/MovementComponent.h"

void CPlayerSpriteAnimationComponent::Initialize()
{
	super::Initialize();

#pragma region IDLE ANIMATION

	vector<FSpriteInfo*> idleSpriteInfos;
	vector<tstring> idleSpritePaths = {
		TEXT("Resources/PlayerCharacter/IDLE/IDLE 1.bmp"),
		TEXT("Resources/PlayerCharacter/IDLE/IDLE 2.bmp"),
		TEXT("Resources/PlayerCharacter/IDLE/IDLE 3.bmp"),
		TEXT("Resources/PlayerCharacter/IDLE/IDLE 4.bmp")
	};

	FSpriteInfo::MakeSpriteInfos(
		idleSpriteInfos, idleSpritePaths, ESpriteDrawType::UseTransparentBlt, FVector(0.5f, 1.0f));
	AddSpriteAnimation(TEXT("Idle"), idleSpriteInfos, 0.3f);

#pragma endregion


#pragma region WALK ANIMATION

	vector<FSpriteInfo*> walkSpriteInfos;
	vector<tstring> walkSpritePaths = {
		TEXT("Resources/PlayerCharacter/WALK/WALK 1.bmp"),
		TEXT("Resources/PlayerCharacter/WALK/WALK 2.bmp"),
		TEXT("Resources/PlayerCharacter/WALK/WALK 3.bmp"),
		TEXT("Resources/PlayerCharacter/WALK/WALK 4.bmp")
	};

	FSpriteInfo::MakeSpriteInfos(
		walkSpriteInfos, walkSpritePaths, ESpriteDrawType::UseTransparentBlt, FVector(0.5f, 1.0f));
	AddSpriteAnimation(TEXT("Walk"), walkSpriteInfos, 0.2f);

#pragma endregion


	// Idle Animation ���
	PlaySpriteAnimation(TEXT("Idle"));
}

void CPlayerSpriteAnimationComponent::Tick(float dt)
{
	super::Tick(dt);

	AnimControl();
}

void CPlayerSpriteAnimationComponent::AnimControl()
{
	// �� ������Ʈ�� �����ϴ� PlayerCharacter �� ����ϴ�.
	CPlayerCharacter* playerCharacter = Cast<CPlayerCharacter>(Owner);

	// PlayerCharacter �� �������� �ʴ´ٸ� ���� X
	if (playerCharacter == nullptr) return;


	// �����ų �ִϸ��̼� �̸��� ��Ÿ���ϴ�.
	tstring animNameToPlay = STOP_ANIMATION;

	// �̵� �ӷ��� ����ϴ�.
	float speed = playerCharacter->GetMovement()->Velocity.Length();

	animNameToPlay = (speed < 0.1f) ? TEXT("Idle") : TEXT("Walk");

	// �̵��ϴ� ���⿡ ���� �̹����� �������ּ���
	/// - �̵�Ű�� �Է����� �ʾ��� ��쿡�� �ٶ󺸴� ������ �״�� �ٶ󺾴ϴ�.



	// ��ܿ��� ������ �ִϸ��̼� ���
	PlaySpriteAnimation(animNameToPlay);
}

#include "PlayerSpriteAnimationComponent.h"

#include "Game/GameObject/Character/PlayerCharacter/PlayerCharacter.h"

#include "Game/Components/Movement/MovementComponent.h"
#include "Game/Components/PlayerCharacterMovementHelper/PlayerCharacterMovementHelperComponent.h"


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


	// Idle Animation 재생
	PlaySpriteAnimation(TEXT("Idle"));
}

void CPlayerSpriteAnimationComponent::Tick(float dt)
{
	super::Tick(dt);

	AnimControl();
}

void CPlayerSpriteAnimationComponent::AnimControl()
{
	// 이 컴포넌트를 소유하는 PlayerCharacter 를 얻습니다.
	CPlayerCharacter* playerCharacter = Cast<CPlayerCharacter>(Owner);

	// PlayerCharacter 가 존재하지 않는다면 실행 X
	if (playerCharacter == nullptr) return;


	// 재생시킬 애니메이션 이름을 나타냅니다.
	tstring animNameToPlay = STOP_ANIMATION;

	// 이동 속력을 얻습니다.
	float speed = playerCharacter->GetMovement()->Velocity.Length();

	animNameToPlay = (speed < 0.1f) ? TEXT("Idle") : TEXT("Walk");


	FlipXY(playerCharacter->GetMovementHelper()->GetLookDirection() == EDirection::Left, false);

	// 상단에서 결정된 애니메이션 재생
	PlaySpriteAnimation(animNameToPlay);
}

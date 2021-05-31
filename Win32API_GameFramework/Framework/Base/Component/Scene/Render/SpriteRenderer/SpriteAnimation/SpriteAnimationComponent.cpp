#include "SpriteAnimationComponent.h"

#include "Framework/Statics/GameplayStatics.h"

#include "Framework/Bitmap/Bitmap.h"

void CSpriteAnimationComponent::Initialize()
{
	super::Initialize();

	SpriteAnimation = nullptr;
	SpriteIndex = 0;
	LastSpriteChangedTime = 0.0f;
}

void CSpriteAnimationComponent::Tick(float dt)
{
	super::Tick(dt);

	LoopAnimation();
}

void CSpriteAnimationComponent::Release()
{
	// 그리는 스프라이트를 비웁니다.
	DrawSpriteInfo = nullptr;

	for (auto iter = SpriteAnimInfos.begin(); iter != SpriteAnimInfos.end(); ++iter)
		CObject::DeleteObject(iter->second);
	SpriteAnimInfos.clear();

	super::Release();
}

void CSpriteAnimationComponent::FlipXY(bool flipX, bool flipY)
{
	if (SpriteAnimation == nullptr) return;

	for (auto iter = SpriteAnimation->SpriteInfos.begin(); 
		iter != SpriteAnimation->SpriteInfos.end(); 
		++iter)
	{
		(*iter)->GetLoadedBitmap()->bIsFlippedX = flipX;
		(*iter)->GetLoadedBitmap()->bIsFlippedY = flipY;
	}
}

void CSpriteAnimationComponent::LoopAnimation()
{
	if (SpriteAnimation == nullptr)
		return;
	else
	{
		auto spriteInfo = (*SpriteAnimation)[SpriteIndex];
		if (spriteInfo) DrawSpriteInfo = spriteInfo;

		// 재생중인 애니메이션의 SpriteDelay 만큼의 시간이 지났다면
		if (CGameplayStatics::GetTime() - LastSpriteChangedTime >= SpriteAnimation->SpriteDelay)
		{
			// 마지막으로 스프라이트를 전환한 시간을 저장합니다.
			LastSpriteChangedTime += SpriteAnimation->SpriteDelay;

			// 스프라이트 인덱스를 다음 인덱스로 설정합니다.
			SpriteIndex = (SpriteIndex == SpriteAnimation->GetLastSpriteIndex()) ? 0 : ++SpriteIndex;
		}
	}
}

void CSpriteAnimationComponent::AddSpriteAnimation(
	tstring newAnimationName, 
	const vector<FSpriteInfo*>& spriteInfos, 
	float spriteDelay)
{
	// 이미 등록된 이름의 애니메이션을 추가하려 한다면
	if (SpriteAnimInfos.find(newAnimationName) != SpriteAnimInfos.end())
	{
		tstring title = TEXT("Error adding sprite animation!");
		tstring msg = TEXT("animation name = ") + newAnimationName;

		LOGF(TEXT("[Error] ") << title << TEXT(" : ") << msg);
		::MessageBox(Hwnd, msg.c_str(), title.c_str(), MB_OK | MB_ICONSTOP);

		return;
	}

	// 스프라이트 애니메이션 정보 생성
	FSpriteAnimInfo* newSpriteAnimInfo = CObject::NewObject<FSpriteAnimInfo>();

	// 스프라이트 애니메이션 정보 초기화
	newSpriteAnimInfo->InitializeSpriteAnimInfo(spriteInfos, spriteDelay);

	// SpriteAnimInfos 에 추가
	SpriteAnimInfos.insert(make_pair(newAnimationName, newSpriteAnimInfo));
}

void CSpriteAnimationComponent::PlaySpriteAnimation(tstring animationName, int32 startIndex)
{
	// 표시 중지
	if (animationName == STOP_ANIMATION)
	{
		SpriteAnimation = nullptr;
		return;
	}

	// 애니메이션 존재 여부 확인
	if (SpriteAnimInfos.find(animationName) == SpriteAnimInfos.end())
	{
		LOGF(TEXT("애니메이션 이름을 찾을 수 없습니다. AnimationName = ") << animationName);
		return;
	}

	// 현재 재생중인 애니메이션과 동일한 애니메이션을 재생시키려 한다면 실행 X
	if (SpriteAnimationName == animationName) return;

	// 재생시키려는 애니메이션 이름 설정
	SpriteAnimationName = animationName;

	// 애니메이션 정보를 받아옵니다.
	SpriteAnimation = SpriteAnimInfos[animationName];

	// 스프라이트 애니메이션 인덱스를 설정합니다.
	SpriteIndex = startIndex;

	// 스프라이트 애니메이션 인덱스가 범위를 초과하지 않도록 합니다.
	SpriteIndex = FMath::Clamp(SpriteIndex, 0, SpriteAnimation->GetLastSpriteIndex());

	// 마지막 전환 시간을 현재 시간으로 설정합니다.
	LastSpriteChangedTime = CGameplayStatics::GetTime();
}

#include "SpriteAnimationComponent.h"

void CSpriteAnimationComponent::Initialize()
{
	super::Initialize();

	SpriteAnimation = nullptr;
	SpriteIndex = 0;
}

void CSpriteAnimationComponent::Release()
{
	// 그리는 스프라이트를 비웁니다.
	SetDrawSpriteInfo(nullptr);

	for (auto iter = SpriteAnimInfos.begin(); iter != SpriteAnimInfos.end(); ++iter)
		CObject::DeleteObject(iter->second);
	SpriteAnimInfos.clear();

	super::Release();
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
}

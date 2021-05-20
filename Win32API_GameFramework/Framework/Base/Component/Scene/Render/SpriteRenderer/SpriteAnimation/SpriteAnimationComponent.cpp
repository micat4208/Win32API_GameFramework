#include "SpriteAnimationComponent.h"

void CSpriteAnimationComponent::Initialize()
{
	super::Initialize();

	SpriteAnimation = nullptr;
	SpriteIndex = 0;
}

void CSpriteAnimationComponent::Release()
{
	// �׸��� ��������Ʈ�� ���ϴ�.
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
	// �̹� ��ϵ� �̸��� �ִϸ��̼��� �߰��Ϸ� �Ѵٸ�
	if (SpriteAnimInfos.find(newAnimationName) != SpriteAnimInfos.end())
	{
		tstring title = TEXT("Error adding sprite animation!");
		tstring msg = TEXT("animation name = ") + newAnimationName;

		LOGF(TEXT("[Error] ") << title << TEXT(" : ") << msg);
		::MessageBox(Hwnd, msg.c_str(), title.c_str(), MB_OK | MB_ICONSTOP);

		return;
	}

	// ��������Ʈ �ִϸ��̼� ���� ����
	FSpriteAnimInfo* newSpriteAnimInfo = CObject::NewObject<FSpriteAnimInfo>();

	// ��������Ʈ �ִϸ��̼� ���� �ʱ�ȭ
	newSpriteAnimInfo->InitializeSpriteAnimInfo(spriteInfos, spriteDelay);

	// SpriteAnimInfos �� �߰�
	SpriteAnimInfos.insert(make_pair(newAnimationName, newSpriteAnimInfo));
}

void CSpriteAnimationComponent::PlaySpriteAnimation(tstring animationName, int32 startIndex)
{
	// ǥ�� ����
	if (animationName == STOP_ANIMATION)
	{
		SpriteAnimation = nullptr;
		return;
	}

	// �ִϸ��̼� ���� ���� Ȯ��
	if (SpriteAnimInfos.find(animationName) == SpriteAnimInfos.end())
	{
		LOGF(TEXT("�ִϸ��̼� �̸��� ã�� �� �����ϴ�. AnimationName = ") << animationName);
		return;
	}

	// ���� ������� �ִϸ��̼ǰ� ������ �ִϸ��̼��� �����Ű�� �Ѵٸ� ���� X
	if (SpriteAnimationName == animationName) return;

	// �����Ű���� �ִϸ��̼� �̸� ����
	SpriteAnimationName = animationName;

	// �ִϸ��̼� ������ �޾ƿɴϴ�.
	SpriteAnimation = SpriteAnimInfos[animationName];

	// ��������Ʈ �ִϸ��̼� �ε����� �����մϴ�.
	SpriteIndex = startIndex;

	// ��������Ʈ �ִϸ��̼� �ε����� ������ �ʰ����� �ʵ��� �մϴ�.
	SpriteIndex = FMath::Clamp(SpriteIndex, 0, SpriteAnimation->GetLastSpriteIndex());
}

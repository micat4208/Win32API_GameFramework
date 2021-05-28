#include "AudioComponent.h"

CAudioComponent::CAudioComponent()
{
	Sound = nullptr;
	Channel = nullptr;
	Volume = 0.5f;
	bIsPlaying = bIsPause = false;
}

void CAudioComponent::Tick(float dt)
{
	super::Tick(dt);

	if (Channel == nullptr) return;

	// ���� ����� Ȯ���մϴ�.
	FMOD_Channel_IsPlaying(Channel, &bIsPlaying);

	// ������̶�� ���� ��� ���¸� �����մϴ�.
	if (bIsPlaying) FMOD_System_Update(SoundSystem);
}

void CAudioComponent::Release()
{
	// ���� ���� ����
	if (Sound) FMOD_Sound_Release(Sound);

	super::Release();
}

void CAudioComponent::InitializeAudioComponent(string path, bool bLoop)
{
	LOG(TEXT("asdasd"));

	// ���带 �����մϴ�.
	FMOD_System_CreateSound(
		SoundSystem,
		path.c_str(),
		(bLoop ? FMOD_LOOP_NORMAL : FMOD_DEFAULT),
		NULL,
		&Sound);
	/// - FMOD_LOOP_NORMAL : ���� ���� ���
	/// - FMOD_DEFAULT : �⺻ ��� ��� ( 1 �� ��� )

	LOG(TEXT("Sound is nullptr = ") << (Sound == nullptr));

}

void CAudioComponent::Play()
{
	if (Sound == nullptr)
	{
		LOGF(TEXT("[Error] Sound is nullptr!"));
		return;
	}

	// ���带 �����ŵ�ϴ�.
	FMOD_System_PlaySound(SoundSystem, Sound, NULL, false, &Channel);
	/// - ���� �ý����� �����մϴ�.
	/// - �÷��� ��ų ���带 �����մϴ�.
	/// - ä�� �׷��� �����մϴ�. ������� ���� �� NULL �� �����մϴ�.
	/// - ä���� �Ͻ� �ߴܽ�ų �������� �����մϴ�.
	/// - �����ų �� ���� ä���� �����մϴ�.
}

void CAudioComponent::Pause()
{
	if (bIsPause)		FMOD_Channel_SetPaused(Channel, bIsPause = false);
	else				FMOD_Channel_SetPaused(Channel, bIsPause = true);
}

void CAudioComponent::Stop()
{
	FMOD_Channel_Stop(Channel);
}

void CAudioComponent::SetVolume(float volume)
{
	volume = FMath::Clamp(volume, AUDIO_VOLUME_MIN, AUDIO_VOLUME_MAX);
	FMOD_Channel_SetVolume(Channel, volume);
}

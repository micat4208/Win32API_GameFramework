#include "AudioComponent.h"
#include "fmod_common.h"

CAudioComponent::CAudioComponent()
{
	Sound = nullptr;
	Channel = nullptr;
	Volume = 0.5f;
	bIsPlaying = false;
	bIsPause = false;
}

void CAudioComponent::Tick(float dt)
{
	super::Tick(dt);

	if (Channel == nullptr)
		return;

	// ���� ����� Ȯ��
	FMOD_Channel_IsPlaying(Channel, &bIsPlaying);

	// ��� ���̶�� ���� ��� ���¸� ����
	if (bIsPlaying)
		FMOD_System_Update(SoundSystem);	
}

void CAudioComponent::Release()
{
	// ���� ���� ����
	if (Sound)
		FMOD_Sound_Release(Sound);
	super::Release();
}

void CAudioComponent::InitializeAudioComponent(string path, bool bLoop)
{	
	// ���带 ����
	FMOD_System_CreateSound(
		SoundSystem,
		path.c_str(),
		(bLoop ? FMOD_LOOP_NORMAL : FMOD_DEFAULT),
		NULL,
		&Sound);

	// FMOD_LOOP_NORMAL : ���� ���� ���
	// FMOD_DEFAULT : �⺻ ��� ��� (1�� ���)
}

void CAudioComponent::Play()
{
	if (Sound == nullptr)
	{
		LOG(TEXT("[Error] Sound is nullptr!"));
		return;
	}

	// ���带 ���
	FMOD_System_PlaySound(SoundSystem, Sound, NULL, false, &Channel);
	// ���� �ý����� ����
	// �÷��� ��ų ���带 ����
	// ä�� �׷��� ����. ������� ���� �� NULL�� ����
	// ä���� �Ͻ� �ߴܽ�ų �������� ����
	// �����ų �� ���� ä���� ����
}

void CAudioComponent::Pause()
{
	if (bIsPause)
	{
		FMOD_Channel_SetPaused(Channel, bIsPause = false);		
	}
	else
	{
		FMOD_Channel_SetPaused(Channel, bIsPause = true);		
	}
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

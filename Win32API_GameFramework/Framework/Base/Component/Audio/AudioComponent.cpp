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

	// 사운드 출력을 확인
	FMOD_Channel_IsPlaying(Channel, &bIsPlaying);

	// 재생 중이라면 사운드 출력 상태를 갱신
	if (bIsPlaying)
		FMOD_System_Update(SoundSystem);	
}

void CAudioComponent::Release()
{
	// 사용된 사운드 해제
	if (Sound)
		FMOD_Sound_Release(Sound);
	super::Release();
}

void CAudioComponent::InitializeAudioComponent(string path, bool bLoop)
{	
	// 사운드를 생성
	FMOD_System_CreateSound(
		SoundSystem,
		path.c_str(),
		(bLoop ? FMOD_LOOP_NORMAL : FMOD_DEFAULT),
		NULL,
		&Sound);

	// FMOD_LOOP_NORMAL : 사운드 무한 재생
	// FMOD_DEFAULT : 기본 재생 방식 (1번 재생)
}

void CAudioComponent::Play()
{
	if (Sound == nullptr)
	{
		LOG(TEXT("[Error] Sound is nullptr!"));
		return;
	}

	// 사운드를 재생
	FMOD_System_PlaySound(SoundSystem, Sound, NULL, false, &Channel);
	// 사운드 시스템을 전달
	// 플레이 시킬 사운드를 전달
	// 채널 그룹을 전달. 사용하지 않을 때 NULL을 전달
	// 채널을 일시 중단시킬 것인지를 결정
	// 재생시킬 때 사용될 채널을 전달
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

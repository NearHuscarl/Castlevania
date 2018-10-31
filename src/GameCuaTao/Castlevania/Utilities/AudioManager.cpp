#include "AudioManager.h"

using namespace Castlevania;

AudioManager::SoundDict AudioManager::soundDict;
float AudioManager::volume;

void AudioManager::LoadContent(ContentManager &content, AudioPathDict audioPathDict)
{
	for (auto const [audioName, path] : audioPathDict)
	{
		soundDict[audioName] = content.Load<Sound>(path);
	}

	// Play sound the first time to 'load' it or the game will be lagged when the
	// first sound effects is actually played. TODO: hacky, need a proper fix

	// Voice management flags
	// The voice management flags are valid only for buffers created with the DSBCAPS_LOCDEFER flag,
	// and are used for sounds that are to play in hardware. These flags enable hardware resources
	// that are already in use to be yielded to the current sound.Only buffers created with the
	// DSBCAPS_LOCDEFER flag are candidates for premature termination.
	// Since we created a primary buffer with DSBCAPS_PRIMARYBUFFER flag (in DSUtil.cpp), the option
	// DSBPLAY_TERMINATEBY_PRIORITY will not be valid, so the sound is not played(?)
	auto dummySound = soundDict.begin()->second;
	if (dummySound != nullptr)
	{
		dummySound->Play(0, DSBPLAY_TERMINATEBY_PRIORITY);
	}
}

void AudioManager::Play(std::string name)
{
	auto sound = soundDict[name];
	if (sound != nullptr)
	{
		sound->Play();
	}
}

void AudioManager::PlaySong(std::string name)
{
	PlayLoop(name);
}

void AudioManager::PlayLoop(std::string name)
{
	auto sound = soundDict[name];
	if (sound != nullptr)
	{
		sound->Play(0, DSBPLAY_LOOPING);
	}
}
void AudioManager::Stop(std::string name)
{
	auto sound = soundDict[name];
	if (sound != nullptr)
	{
		sound->Stop();
	}
}

bool AudioManager::IsPlaying(std::string name)
{
	auto sound = soundDict[name];
	if (sound != nullptr)
	{
		return sound->IsSoundPlaying();
	}
	return false;
}
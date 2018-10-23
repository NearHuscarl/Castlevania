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
	//auto dummySound = soundDict.begin()->second;
	//if (dummySound != nullptr)
	//{
	//	dummySound->Play(0, 0, DSBVOLUME_MIN);
	//}
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
#include "AudioManager.h"

std::map<std::string, std::shared_ptr<Sound>> AudioManager::soundDict;
float AudioManager::volume;

void AudioManager::LoadResource(ContentManager &contentManager, std::vector<std::string> sounds)
{
	for (auto sound : sounds)
	{
		soundDict[sound] = contentManager.Load<Sound>(sound + ".wav");
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
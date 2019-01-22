#include "AudioManager.h"

using namespace Castlevania;

AudioManager::SoundDict AudioManager::soundDict;
float AudioManager::volume;

void AudioManager::LoadContent(ContentManager &content)
{
	for (auto const &[audioName, path] : GAME_AUDIO)
	{
		soundDict[audioName] = content.Load<Sound>(path);
	}

	// Play sound the first time to 'load' it or the game will be lagged when the
	// first sound effects is actually played. TODO: hacky, need a proper fix
	Play(M_INTRO_SCENE);
	Stop(M_INTRO_SCENE);
}

void AudioManager::Play(std::string name)
{
	auto sound = soundDict[name];
	if (sound != nullptr)
	{
		sound->Play();
	}
}

void AudioManager::PlayOneInstance(std::string name)
{
	auto sound = soundDict[name];
	if (sound != nullptr)
	{
		if (!IsPlaying(name))
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

void AudioManager::StopAll()
{
	for (auto const &[name, sound] : soundDict)
	{
		if (sound != nullptr)
			sound->Stop();
	}
}

void AudioManager::Resume(std::string name)
{
	auto sound = soundDict[name];
	if (sound != nullptr)
	{
		sound->Resume();
	}
}

void AudioManager::Reset(std::string name)
{
	auto sound = soundDict[name];
	if (sound != nullptr)
	{
		sound->Reset();
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
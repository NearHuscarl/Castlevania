#pragma once

#include "Direct2DGame/Content/ContentManager.h"

using AudioPathDict = std::map<std::string, std::string>;

namespace Castlevania
{
	class AudioManager
	{
	public:
		static void LoadContent(ContentManager &content, AudioPathDict audioPathDict);

		static void Play(std::string name);
		static void PlaySong(std::string name);
		static void PlayLoop(std::string name);

		static void Stop(std::string name);
		static bool IsPlaying(std::string name);

	private:
		using SoundDict = std::map<std::string, std::shared_ptr<Sound>>;
		
		static SoundDict soundDict;
		static float volume;
	};
}
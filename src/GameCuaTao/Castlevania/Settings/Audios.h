#pragma once

#include <string>
#include <map>

namespace Castlevania
{
	constexpr auto WHIPPING = "WHIPPING";
	constexpr auto GAME_START_PROLOGUE = "GAME_START_PROLOGUE";

	const auto GAME_AUDIO = std::map<std::string, std::string>
	{
		{ GAME_START_PROLOGUE,  "Sounds/Musics/Game_Start_Prologue.wav" },
		{ WHIPPING,             "Sounds/SoundEffects/Whipping.wav" },
	};
}
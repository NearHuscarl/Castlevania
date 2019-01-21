#pragma once

#include <string>
#include <unordered_map>

namespace Castlevania
{
	using AudioInfo = std::unordered_map<std::string, std::string>;

	constexpr auto M_INTRO_SCENE = "INTRO_SCENE_MUSIC";
	constexpr auto M_BLOCK_01 = "BLOCK_01_MUSIC";
	constexpr auto M_BOSS_BATTLE = "BOSS_BATTLE_MUSIC";
	constexpr auto M_GAME_OVER = "GAME_OVER_MUSIC";

	constexpr auto SE_BEING_HIT = "SE_BEING_HIT";
	constexpr auto SE_FISHMAN_LAUNCHING = "SE_FISHMAN_LAUNCHING";
	constexpr auto SE_GETTING_HEART = "SE_GETTING_HEART";
	constexpr auto SE_GETTING_HEART_BONUS = "SE_GETTING_HEART_BONUS";
	constexpr auto SE_GETTING_HOLY_CROSS = "SE_GETTING_HOLY_CROSS";
	constexpr auto SE_GETTING_MONEY_BAG = "SE_GETTING_MONEY_BAG";
	constexpr auto SE_GETTING_POWERUP = "SE_GETTING_POWERUP";
	constexpr auto SE_GETTING_TIME_BONUS = "SE_GETTING_TIME_BONUS";
	constexpr auto SE_GOING_TO_CASTLE = "SE_GOING_TO_CASTLE";
	constexpr auto SE_HIDDEN_MONEY_BAG_FOUND = "SE_HIDDEN_MONEY_BAG_FOUND";
	constexpr auto SE_HITTING_BREAKABLE_BLOCK = "SE_HITTING_BREAKABLE_BLOCK";
	constexpr auto SE_HITTING_SOMETHING = "SE_HITTING_SOMETHING";
	constexpr auto SE_HITTING_WATER_SURFACE = "SE_HITTING_WATER_SURFACE";
	constexpr auto SE_HOLY_WATER_TOUCHING_GROUND = "SE_HOLY_WATER_TOUCHING_GROUND";
	constexpr auto SE_INVISIBLE_END = "SE_INVISIBLE_END";
	constexpr auto SE_INVISIBLE_START = "SE_INVISIBLE_START";
	constexpr auto SE_LANDING = "SE_LANDING";
	constexpr auto SE_LIVE_LOST = "SE_LIVE_LOST";
	constexpr auto SE_STAGE_CLEAR = "SE_STAGE_CLEAR";
	constexpr auto SE_STOPWATCH_START = "SE_STOPWATCH_START";
	constexpr auto SE_THROWING_DAGGER = "SE_THROWING_DAGGER";
	constexpr auto SE_TIMEOUT_WARNING = "SE_TIMEOUT_WARNING";
	constexpr auto SE_USING_DOOR = "SE_USING_DOOR";
	constexpr auto SE_USING_WEAPON = "SE_USING_WEAPON";

	const auto GAME_AUDIO = AudioInfo
	{
		// Musics
		{ M_INTRO_SCENE,  "Sounds/Musics/Game_Start_Prologue.wav" },
		{ M_BLOCK_01,     "Sounds/Musics/Stage_01_Vampire_Killer.wav" },
		{ M_BOSS_BATTLE,  "Sounds/Musics/Boss_Battle_Poison_Mind.wav" },
		{ M_GAME_OVER,    "Sounds/Musics/Game_Over.wav" },

		// Sound effects
		{ SE_BEING_HIT,                  "Sounds/SoundEffects/Being_Hit.wav" }, // simon taking damage from enemies
		{ SE_FISHMAN_LAUNCHING,          "Sounds/SoundEffects/Fishman_Launching.wav" },
		{ SE_GETTING_HEART,              "Sounds/SoundEffects/Getting_Heart.wav" },
		{ SE_GETTING_HEART_BONUS,        "Sounds/SoundEffects/Getting_Heart_Bonus.wav" },
		{ SE_GETTING_HOLY_CROSS,         "Sounds/SoundEffects/Getting_Holy_Cross.wav" },
		{ SE_GETTING_MONEY_BAG,          "Sounds/SoundEffects/Getting_Money_Bag.wav" },
		// get other powerups except hearts, moneybag, holy cross, stopwatch and invisible jar
		{ SE_GETTING_POWERUP,            "Sounds/SoundEffects/Getting_Powerup.wav" },
		{ SE_GETTING_TIME_BONUS,         "Sounds/SoundEffects/Getting_Time_Bonus.wav" },
		{ SE_GOING_TO_CASTLE,            "Sounds/SoundEffects/Going_To_Castle.wav" },
		{ SE_HIDDEN_MONEY_BAG_FOUND,     "Sounds/SoundEffects/Hidden_Money_Bag_Found.wav" },
		{ SE_HITTING_BREAKABLE_BLOCK,    "Sounds/SoundEffects/Hitting_Breakable_Block.wav" },
		// simon's weapon hit candles, enemies, fireballs,...
		{ SE_HITTING_SOMETHING,          "Sounds/SoundEffects/Hitting_Something.wav" },
		{ SE_HITTING_WATER_SURFACE,      "Sounds/SoundEffects/Hitting_Water_Surface.wav" },
		{ SE_HOLY_WATER_TOUCHING_GROUND, "Sounds/SoundEffects/Holy_Water_Touching_Ground.wav" },
		{ SE_INVISIBLE_END,              "Sounds/SoundEffects/Invisible_End.wav" },
		{ SE_INVISIBLE_START,            "Sounds/SoundEffects/Invisible_Start.wav" },
		{ SE_LANDING,                    "Sounds/SoundEffects/Landing.wav" },
		{ SE_LIVE_LOST,                  "Sounds/SoundEffects/Live_Lost_.wav" },
		{ SE_STAGE_CLEAR,                "Sounds/SoundEffects/Stage_Clear_.wav" },
		{ SE_STOPWATCH_START,            "Sounds/SoundEffects/Stopwatch_Start.wav" },
		{ SE_THROWING_DAGGER,            "Sounds/SoundEffects/Throwing_Dagger.wav" },
		{ SE_TIMEOUT_WARNING,            "Sounds/SoundEffects/Timeout_Warning.wav" },
		{ SE_USING_DOOR,                 "Sounds/SoundEffects/Using_Door.wav" },
		// when whipping or throwing axe
		{ SE_USING_WEAPON,               "Sounds/SoundEffects/Using_Weapon.wav" },
	};
}
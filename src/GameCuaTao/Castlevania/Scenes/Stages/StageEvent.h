#pragma once

namespace Castlevania
{
	constexpr auto NEXT_ROOM_CUTSCENE_STARTED = 0;
	constexpr auto NEXT_ROOM_CUTSCENE_ENDED = 1;
	constexpr auto NEXT_MAP_CUTSCENE_STARTED = 2;
	constexpr auto NEXT_MAP_CUTSCENE_ENDED = 3;
	constexpr auto BOSS_FIGHT_CUTSCENE_STARTED = 4;
	constexpr auto CUTSCENE_ENDED = 5;
	constexpr auto PLAYER_DIE = 6;
	constexpr auto BOSS_DIE = 7;
	constexpr auto LEVEL_COMPLETED = 8;
	constexpr auto RESET_STAGE_CUTSCENE_ENDED = 9;
	constexpr auto GAME_OVER = 10;

	// Those powerups affect many entities at the same time so Stage will handle it
	constexpr auto CROSS_POWERUP_ACTIVATED = 11;
	constexpr auto STOPWATCH_POWERUP_ACTIVATED = 12;

	constexpr auto HIDDEN_MONEY_BAG_FOUND = 13;

	// Courtyard events
	constexpr auto GO_TO_CASTLE_CUTSCENE_STARTED = 14;

}
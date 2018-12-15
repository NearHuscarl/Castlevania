#pragma once

namespace Castlevania
{
	constexpr auto NEXT_ROOM_CUTSCENE_STARTED = 0;
	constexpr auto NEXT_ROOM_CUTSCENE_ENDED = 1;
	constexpr auto NEXT_MAP_CUTSCENE_STARTED = 2;
	constexpr auto NEXT_MAP_CUTSCENE_ENDED = 3;
	constexpr auto PLAYER_DIE = 4;
	constexpr auto RESET_STAGE_CUTSCENE_ENDED = 5;
	constexpr auto GAME_OVER = 6;

	// Courtyard events
	constexpr auto GO_TO_CASTLE_CUTSCENE_STARTED = 7;
	constexpr auto GO_TO_CASTLE_CUTSCENE_ENDED = 8;
}
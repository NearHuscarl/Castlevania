#pragma once

namespace Castlevania
{
	constexpr auto GRAVITY = 23.0f;

	// -- Events --

	// Common
	constexpr auto STATE_CHANGED = 0;
	constexpr auto VISIBILITY_CHANGED = 1;
	constexpr auto FACING_CHANGED = 2;

	// Player events
	constexpr auto MOVE_STATE_CHANGED = 3;
	constexpr auto ATTACK_STATE_CHANGED = 4;
	constexpr auto UNTOUCHABLE_ENDED = 5;

	// Panther events
	constexpr auto PLAYER_IN_RANGE = 6;

	// WaterArea events
	constexpr auto OBJECT_HITS_WATER_SURFACE = 7;
}
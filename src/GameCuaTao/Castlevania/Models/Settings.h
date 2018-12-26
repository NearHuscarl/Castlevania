#pragma once

namespace Castlevania
{
	constexpr auto GRAVITY = 23.0f;

	// -- Events --

	// Common
	constexpr auto STATE_CHANGED = 0;
	constexpr auto FACING_CHANGED = 1;
	constexpr auto TAKING_DAMAGE = 2;

	// Player events
	constexpr auto MOVE_STATE_CHANGED = 3;
	constexpr auto ATTACK_STATE_CHANGED = 4;
	constexpr auto UNTOUCHABLE_ENDED = 5;
	constexpr auto INVISIBLE_ENDED = 6;

	// Whip events
	constexpr auto WHIP_UNLEASHED = 7;
	constexpr auto WHIP_WITHDRAWN = 8;

	// Enemy events
	constexpr auto PLAYER_IN_RANGE = 9;
	constexpr auto PLAYER_OUT_OF_RANGE = 10;
	constexpr auto ACTIVE_CHANGED = 11;

	// GiantBat events
	constexpr auto PLAYER_IN_THREAT_ZONE = 12;

	// WaterArea events
	constexpr auto OBJECT_HITS_WATER_SURFACE = 13;
}
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
	constexpr auto GOD_MODE_ACTIVATED = 7;
	constexpr auto GOD_MODE_DEACTIVATED = 8;

	// Whip events
	constexpr auto WHIP_UNLEASHED = 9;
	constexpr auto WEAPON_WITHDRAWN = 10;

	// Enemy events
	constexpr auto PLAYER_IN_RANGE = 11;
	constexpr auto PLAYER_OUT_OF_RANGE = 12;
	constexpr auto ACTIVE_CHANGED = 13;

	// GiantBat events
	constexpr auto PLAYER_IN_THREAT_ZONE = 14;

	// WaterArea events
	constexpr auto OBJECT_HITS_WATER_SURFACE = 15;
}
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
	constexpr auto UNTOUCHABLE_STARTED = 5;
	constexpr auto UNTOUCHABLE_ENDED = 6;
	constexpr auto INVISIBLE_STARTED = 7;
	constexpr auto INVISIBLE_ENDED = 8;
	constexpr auto GOD_MODE_ACTIVATED = 9;
	constexpr auto GOD_MODE_DEACTIVATED = 10;

	// Whip events
	constexpr auto WHIP_UNLEASHED = 11;
	constexpr auto WEAPON_WITHDRAWN = 12;

	// Enemy events
	constexpr auto PLAYER_IN_RANGE = 13;
	constexpr auto PLAYER_OUT_OF_RANGE = 14;
	constexpr auto ACTIVE_CHANGED = 15;

	// GiantBat events
	constexpr auto PLAYER_IN_THREAT_ZONE = 16;

	// WaterArea events
	constexpr auto OBJECT_HITS_WATER_SURFACE = 17;
}
#pragma once

namespace Castlevania
{
	constexpr auto GRAVITY = 23.0f;

	// -- Events --

	// Common
	constexpr auto STATE_CHANGED = 0;
	constexpr auto ENABLED_CHANGED = 0;
	constexpr auto FACING_CHANGED = 1;

	// Player events
	constexpr auto MOVE_STATE_CHANGED = 2;
	constexpr auto ATTACK_STATE_CHANGED = 3;
	constexpr auto UNTOUCHABLE_ENDED = 4;

	// Panther events
	constexpr auto NEAR_PLAYER = 5;
}
#pragma once

namespace Castlevania
{
	constexpr auto GRAVITY = 23.0f;

	// -- Events --

	// Common
	constexpr auto STATE_CHANGED = 0;

	// Player events
	constexpr auto MOVE_STATE_CHANGED = 1;
	constexpr auto ATTACK_STATE_CHANGED = 2;
	constexpr auto UNTOUCHABLE_ENDED = 3;

	// Panther events
	constexpr auto NEAR_PLAYER = 4;
}
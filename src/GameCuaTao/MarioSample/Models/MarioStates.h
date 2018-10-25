#pragma once

#include <string>

namespace MarioSample
{
	enum State
	{
		WALK_LEFT,
		WALK_RIGHT,
		IDLE,
		JUMP,
	};

	// Animation types
	constexpr auto MARIO_WALK = "mario_walk";
	constexpr auto MARIO_IDLE = "mario_idle";
	constexpr auto MARIO_JUMP = "mario_jump";
}
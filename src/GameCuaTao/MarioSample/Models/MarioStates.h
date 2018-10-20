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

	constexpr auto MARIO_WALK = "mario_walk";
	constexpr auto MARIO_IDLE = "mario_idle";
	constexpr auto MARIO_JUMP = "mario_jump";

	const std::map<State, std::string> STATE_TO_ANIMATION =
	{
		{ State::WALK_LEFT, MARIO_WALK },
		{ State::WALK_RIGHT, MARIO_WALK },
		{ State::IDLE, MARIO_IDLE },
		{ State::JUMP, MARIO_JUMP },
	};
}
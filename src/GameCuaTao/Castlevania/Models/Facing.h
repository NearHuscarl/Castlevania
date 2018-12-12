#pragma once

#include "Direct2DGame/Extensions/Direction.h"

namespace Castlevania
{
	enum class Facing
	{
		Right,
		Left,
		None,
	};

	Facing Opposite(Facing facing);
	Facing Direction2Facing(Direction direction);
}
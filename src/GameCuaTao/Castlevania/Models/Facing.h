#pragma once

namespace Castlevania
{
	enum class Facing
	{
		Right,
		Left,
		None,
	};

	Facing Opposite(Facing facing);
}
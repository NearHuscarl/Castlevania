#pragma once

namespace Castlevania
{
	enum class Map
	{
		INTRO,
		COURTYARD,
		GREAT_HALL,
		UNDERGROUND,
		PLAYGROUND,
	};

	const auto MAP_BLACK_COLOR = Color{ 5, 5, 5, 255 };
	const auto MAP_WHITE_COLOR = Color{ 188, 188, 188, 255 };
	const auto MAP_COLORKEY = MAP_BLACK_COLOR;
}
#pragma once

enum class Direction
{
	Left,
	Top,
	Right,
	Bottom,
	None,
};

Direction Opposite(Direction input);
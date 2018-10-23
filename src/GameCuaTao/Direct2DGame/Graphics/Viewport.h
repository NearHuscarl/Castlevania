#pragma once

#include "../Base/Vector.h"

struct Viewport
{
	int X;
	int Y;
	int Width;
	int Height;

	// Get position relative to screen space from world space position
	Vector Project(Vector source)
	{
		return Vector{ source.x - X, source.y - Y };
	}

	// Get position relative to world space from screen space position
	Vector Unproject(Vector source)
	{
		return Vector{ source.x + X, source.y + Y };
	}
};
#pragma once

#include "../Base/Vector2.h"

struct Viewport
{
	int X;
	int Y;
	int Width;
	int Height;

	// Get position relative to screen space from world space position
	Vector2 Project(Vector2 source)
	{
		return Vector2{ source.x - X, source.y - Y };
	}

	// Get position relative to world space from screen space position
	Vector2 Unproject(Vector2 source)
	{
		return Vector2{ source.x + X, source.y + Y };
	}
};
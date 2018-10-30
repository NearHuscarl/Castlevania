#pragma once

#include "../Base/Vector2.h"

struct Viewport
{
	int x;
	int y;
	int width;
	int height;

	// Get position relative to screen space from world space position
	Vector2 Project(Vector2 source)
	{
		return Vector2{ source.x - x, source.y - y };
	}

	// Get position relative to world space from screen space position
	Vector2 Unproject(Vector2 source)
	{
		return Vector2{ source.x + x, source.y + y };
	}
};
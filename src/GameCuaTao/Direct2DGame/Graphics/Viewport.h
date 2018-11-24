#pragma once

#include "../Base/Vector2.h"
#include "../Extensions/RectF.h"

struct Viewport
{
	float x;
	float y;
	int width;
	int height;

	Vector2 Project(float x, float y)
	{
		return Project(Vector2{ x, y });
	}

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

	RectF Bounds()
	{
		return RectF{ x, y, (float)width, (float)height };
	}
};
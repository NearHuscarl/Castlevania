#include <math.h>
#include "Viewport.h"

Vector2 Viewport::Project(float x, float y)
{
	return Project(Vector2{ x, y });
}

Vector2 Viewport::Project(Vector2 source)
{
	auto viewport_x = roundf(x);
	auto viewport_y = roundf(y);

	return Vector2{
		source.x - viewport_x,
		source.y - viewport_y };
}

Vector2 Viewport::Unproject(Vector2 source)
{
	auto viewport_x = roundf(x);
	auto viewport_y = roundf(y);

	return Vector2{
		source.x + viewport_x,
		source.y + viewport_y };
}

RectF Viewport::Bounds()
{
	return RectF{ x, y, (float)width, (float)height };
}

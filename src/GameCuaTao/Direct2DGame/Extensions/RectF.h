#pragma once

#include "../Base/Vector2.h"
#include "../Base/Rect.h"

// A rectangle but store value in float, is used to calculate bounding box for
// real-time collision detection
struct RectF
{
	float left;
	float top;
	float right;
	float bottom;

	RectF();
	RectF(float left, float top, float width, float height);

	float X();
	float Y();
	float Width();
	float Height();

	Vector2 GetPosition();
	static RectF Empty();

	bool operator==(RectF other);
	bool Contains(RectF value);
	bool Intersects(RectF value);
	bool TouchesOrIntersects(RectF value);

	explicit operator Rect();
};
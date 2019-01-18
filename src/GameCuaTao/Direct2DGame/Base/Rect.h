#pragma once

#include <vector>
#include <windows.h>
#include "Point.h"
#include "Vector2.h"

struct RectF;

struct Rect : public RECT
{
	Rect();
	Rect(int left, int top, int width, int height);
	
	int X();
	int Y();
	int Width();
	int Height();

	Point Center();
	static Rect Empty();

	bool operator==(Rect other);
	bool operator!=(Rect other);
	bool Contains(Rect value);
	bool Contains(Vector2 value);
	bool Intersects(Rect value);
	bool TouchesOrIntersects(Rect value);

	static Rect Merge(Rect value1, Rect value2);
	static std::vector<Rect> Split(Rect origin, int childWidth, int childHeight);

	operator RectF(); // Implicit conversion
};
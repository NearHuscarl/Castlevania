#pragma once

#include <windows.h>
#include "Point.h"

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
	bool Contains(Rect value);
};
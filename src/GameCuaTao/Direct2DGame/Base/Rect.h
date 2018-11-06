#pragma once

#include <windows.h>
#include "Point.h"

struct Rect : public RECT
{
	Rect() : Rect(0, 0, 0, 0)
	{
	}

	Rect(int left, int top, int width, int height)
	{
		this->left = left;
		this->top = top;
		this->right = left + width;
		this->bottom = top + height;
	}

	int X()
	{
		return left;
	}

	int Y()
	{
		return top;
	}

	int Width()
	{
		return right - left;
	}

	int Height()
	{
		return bottom - top;
	}

	Point Center()
	{
		return Point{ X() + Width() / 2, Y() + Height() / 2 };
	}

	static Rect Empty()
	{
		static auto emptyRectangle = Rect{};
		return emptyRectangle;
	}

	bool operator==(Rect other)
	{
		return (
			this->X() == other.X() &&
			this->Y() == other.Y() &&
			this->Width() == other.Width() &&
			this->Height() == other.Height());
	}
};
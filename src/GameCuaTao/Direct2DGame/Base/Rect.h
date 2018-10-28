#pragma once

#include <windows.h>

struct Rect : RECT
{
	Rect()
	{
		Rect(0, 0, 0, 0);
	}

	Rect(int left, int top, int right, int bottom)
	{
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
	}

	int Width()
	{
		return right - left;
	}

	int Height()
	{
		return bottom - top;
	}
};
#pragma once

#include <windows.h>

struct BoundingBox : RECT
{
	BoundingBox()
	{
		BoundingBox(0, 0, 0, 0);
	}

	BoundingBox(int left, int top, int right, int bottom)
	{
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
	}
};
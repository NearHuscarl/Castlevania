#pragma once

#include "../Direct3D9.h"

struct Vector2 : D3DXVECTOR2
{
	Vector2()
	{
		x = y = 0;
	}

	Vector2(float x, float y) : D3DXVECTOR2(x, y)
	{
	}

	static Vector2 Zero()
	{
		static auto zeroVector = Vector2{ 0, 0 };
		return zeroVector;
	}
};
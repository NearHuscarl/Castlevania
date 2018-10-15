#pragma once

#include <d3dx9.h>

struct Vector : D3DXVECTOR3
{
	Vector()
	{
		x = y = z = 0;
	}

	Vector(float x, float y, float z = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};
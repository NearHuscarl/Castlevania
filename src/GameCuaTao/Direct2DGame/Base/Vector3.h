#pragma once

#include "Vector2.h"

struct Vector3 : public D3DXVECTOR3
{
	Vector3(Vector2 vector)
	{
		x = vector.x;
		y = vector.y;
		z = 0;
	}
};
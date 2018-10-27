#pragma once

#include <d3dx9.h>
#include "Vector2.h"

struct Vector3 : D3DXVECTOR3
{
	Vector3(Vector2 vector)
	{
		x = vector.x;
		y = vector.y;
		z = 0;
	}
};
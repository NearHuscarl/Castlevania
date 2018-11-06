#pragma once

#include "Base/Vector2.h"

class MathHelper
{
public:
	static int Min(int value1, int value2);
	static float Max(float value1, float value2);

	static float ToRadians(float degrees);
	static Vector2 Degrees2Vector(float degrees);

private:
	static const double PI_180;
};
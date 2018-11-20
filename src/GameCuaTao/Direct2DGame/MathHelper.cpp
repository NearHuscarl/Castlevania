#include <cmath>
#include <stdlib.h> // srand, rand
#include "MathHelper.h"

double const MathHelper::PI_180 = 0.0174532925199432957;

float MathHelper::ToRadians(float degrees)
{
	return (float)(degrees * PI_180); // 1 degree = pi / 180 radians
}

Vector2 MathHelper::Degrees2Vector(float degrees)
{
	auto radian = ToRadians(degrees);
	auto x = std::cos(radian);
	auto y = std::sin(radian);

	return Vector2(x, y);
}

int MathHelper::RandomBetween(int min, int max)
{
	return rand() % (max - min) + min;
}

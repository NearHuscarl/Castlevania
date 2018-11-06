#include <cmath>
#include "MathHelper.h"

double const MathHelper::PI_180 = 0.0174532925199432957;

int MathHelper::Min(int value1, int value2)
{
	return value1 < value2 ? value1 : value2;
}

float MathHelper::Max(float value1, float value2)
{
	return value1 > value2 ? value1 : value2;
}

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

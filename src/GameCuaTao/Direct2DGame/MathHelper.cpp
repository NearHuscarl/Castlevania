#include <cmath>
#include <math.h>
#include <stdlib.h> // srand, rand
#include "MathHelper.h"

double const MathHelper::PI = 3.14159265358979323846;
double const MathHelper::TWO_PI = PI * 2;
double const MathHelper::PI_180 = PI / 180;

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

bool MathHelper::RandomBoolean()
{
	return rand() % 2 == 0 ? true : false;
}

bool MathHelper::RandomPercent(float percentValue)
{
	return RandomBetween(1, 100) < percentValue;
}

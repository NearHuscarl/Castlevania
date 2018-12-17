#include <math.h>
#include "Vector2.h"

Vector2::Vector2()
{
	x = y = 0;
}

Vector2::Vector2(float x, float y) : D3DXVECTOR2{ x, y }
{
}

Vector2 Vector2::Zero()
{
	static auto zeroVector = Vector2{ 0, 0 };
	return zeroVector;
}

Vector2 Vector2::One()
{
	static auto oneVector = Vector2{ 1, 1 };
	return oneVector;
}

Vector2 Vector2::operator*(const Vector2 & value) const
{
	return Vector2{ this->x * value.x, this->y * value.y };
}

Vector2 Vector2::operator=(const D3DXVECTOR2 & value) const
{
	return Vector2{ value.x, value.y };
}

Vector2 Vector2::operator+(const Vector2 & value) const
{
	return Vector2{ this->x + value.x, this->y + value.y };
}

Vector2 Vector2::operator-(const Vector2 & value) const
{
	return Vector2{ this->x - value.x, this->y - value.y };
}

Vector2 Vector2::operator+(const float value) const
{
	return Vector2{ this->x + value, this->y + value };
}

Vector2 Vector2::operator-(const float value) const
{
	return Vector2{ this->x - value, this->y - value };
}

Vector2 Vector2::operator*(const float value) const
{
	return Vector2{ this->x * value, this->y * value };
}

Vector2 Vector2::operator/(const float value) const
{
	return Vector2{ this->x / value, this->y / value };
}

float Vector2::Distance(Vector2 value1, Vector2 value2)
{
	auto dx = value1.x - value2.x;
	auto dy = value1.y - value2.y;

	return (float)sqrt((dx * dx) + (dy * dy));
}

float Vector2::Length()
{
	return (float)sqrt((x * x) + (y * y));
}

Vector2 Vector2::Normalize(Vector2 value)
{
	auto val = 1 / value.Length();
	
	value.x *= val;
	value.y *= val;

	return value;
}

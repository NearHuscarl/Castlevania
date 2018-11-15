#pragma once

#include "../Direct3D9.h"

struct Vector2 : public D3DXVECTOR2
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

	static Vector2 One()
	{
		static auto oneVector = Vector2{ 1, 1 };
		return oneVector;
	}

	using D3DXVECTOR2::operator*;

	Vector2 operator*(const Vector2 &value) const
	{
		return Vector2(this->x * value.x, this->y * value.y);
	}

	Vector2 operator=(const D3DXVECTOR2 &value) const
	{
		return Vector2(value.x, value.y);
	}

	Vector2 operator-(const D3DXVECTOR2 &value) const
	{
		return *this - value;
	}

	Vector2 operator+(const float value) const
	{
		return Vector2{ this->x + value, this->y + value };
	}

	Vector2 operator-(const float value) const
	{
		return Vector2{ this->x - value, this->y - value };
	}

	Vector2 operator*(const float value) const
	{
		return Vector2{ this->x * value, this->y * value };
	}

	Vector2 operator/(const float value) const
	{
		return Vector2{ this->x / value, this->y / value };
	}
};
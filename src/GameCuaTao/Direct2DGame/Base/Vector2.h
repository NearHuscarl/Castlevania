#pragma once

#include "../Direct3D9.h"

struct Vector2 : public D3DXVECTOR2
{
	Vector2();
	Vector2(float x, float y);

	static Vector2 Zero();
	static Vector2 One();

	using D3DXVECTOR2::operator*;

	Vector2 operator*(const Vector2 &value) const;
	Vector2 operator=(const D3DXVECTOR2 &value) const;
	Vector2 operator+(const Vector2 &value) const;
	Vector2 operator-(const Vector2 &value) const;
	Vector2 operator+(const float value) const;
	Vector2 operator-(const float value) const;
	Vector2 operator*(const float value) const;
	Vector2 operator/(const float value) const;

	static float Distance(Vector2 value1, Vector2 value2);
	float Length();
};
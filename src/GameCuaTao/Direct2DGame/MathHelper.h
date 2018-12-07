#pragma once

#include "Base/Vector2.h"

class MathHelper
{
public:
	static const double PI;
	static const double TWO_PI;
	static const double PI_180;

	template<typename T>
	static T Clamp(T value, T min, T max);

	template<typename T>
	static T Min(T value1, T value2);

	template<typename T>
	static T Max(T value1, T value2);

	static float ToRadians(float degrees);
	static Vector2 Degrees2Vector(float degrees);

	template<typename T>
	static int RandomBetween(T min, T max);
	// Like RandomBetween(int, int) but do not repeat oldValue
	template<typename T>
	static int RandomBetween(T min, T max, T oldValue);
};

template<typename T>
inline T MathHelper::Clamp(T value, T min, T max)
{
	value = (value < min) ? min : value;
	value = (value > max) ? max : value;

	return value;
}

template<typename T>
inline T MathHelper::Min(T value1, T value2)
{
	return (value1 < value2) ? value1 : value2;
}

template<typename T>
inline T MathHelper::Max(T value1, T value2)
{
	return (value1 > value2) ? value1 : value2;
}

template<typename T>
inline int MathHelper::RandomBetween(T min, T max)
{
	return rand() % (max - min) + min;
}

template<typename T>
inline int MathHelper::RandomBetween(T min, T max, T oldValue)
{
	auto newValue = RandomBetween(min, max);

	while (newValue == oldValue)
	{
		newValue = RandomBetween(min, max);
	}

	return newValue;
}

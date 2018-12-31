#pragma once

#include <math.h>
#include <random>
#include <iterator>
#include "Base/Vector2.h"

class MathHelper
{
public:
	static const double PI;
	static const double TWO_PI;
	static const double PI_180;

	template<typename T>
	static T Clamp(T value, T min, T max);

	static float Lerp(float value1, float value2, float amount);

	template<typename T>
	static T Min(T value1, T value2);

	template<typename T>
	static T Max(T value1, T value2);

	static float ToRadians(float degrees);
	static Vector2 Degrees2Vector(float degrees);

	static Vector2 RandomDirection(float minAngle = 0.0f, float maxAngle = 360.0f);
	static bool RandomBoolean();
	static bool RandomPercent(float percentValue); // 1-100

	static int RandomBetween(int min, int max);
	static float RandomBetween(float min, float max);

	// Like RandomBetween(int, int) but do not repeat oldValue
	template<typename T>
	static T RandomBetween(T min, T max, T oldValue);

	// https://stackoverflow.com/a/16421677/9449426
	template<typename Iter, typename RandomGenerator>
	static Iter RandomItem(Iter start, Iter end, RandomGenerator& g);

	// int r = *RandomItem(foo.begin(), foo.end());
	template<typename Iter>
	static Iter RandomItem(Iter start, Iter end);
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
inline T MathHelper::RandomBetween(T min, T max, T oldValue)
{
	auto newValue = RandomBetween(min, max);

	while (newValue == oldValue)
	{
		newValue = RandomBetween(min, max);
	}

	return newValue;
}

template<typename Iter>
inline Iter MathHelper::RandomItem(Iter start, Iter end)
{
	static auto rd = std::random_device{};
	static auto gen = std::mt19937{ rd() };

	return RandomItem(start, end, gen);
}

template<typename Iter, typename RandomGenerator>
inline Iter MathHelper::RandomItem(Iter start, Iter end, RandomGenerator &g)
{
	std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
	std::advance(start, dis(g));

	return start;
}

#pragma once

#include "TimeSpan.h"

struct GameTime
{
public:
	TimeSpan TotalGameTime = TimeSpan::Zero();
	TimeSpan ElapsedGameTime = TimeSpan::Zero();

	long GetPreviousTicks()
	{
		return previousTicks;
	}

	void SetPreviousTicks(long tick)
	{
		previousTicks = tick;
	}

private:
	long previousTicks;
};
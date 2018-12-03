#pragma once

#include "Direct2DGame/Utilities/Stopwatch.h"

namespace Castlevania
{
	class Timer
	{
	public:
		// interval in seconds
		Timer(int startingTime = 0);

		void SetCounter(int counter);
		void ResetLastSecond();
		int GetCounter() const;

		void CountDown();

	private:
		int counter;
		Stopwatch stopwatch;
	};
}
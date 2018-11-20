#include "Timer.h"

using namespace Castlevania;

Timer::Timer(int startingTime)
{
	counter = startingTime;
	stopwatch.Start();
}

void Timer::SetCounter(int counter)
{
	this->counter = counter;
}

int Timer::GetCounter() const
{
	return counter;
}

void Timer::CountDown()
{
	if (stopwatch.ElapsedMilliseconds() > 1000)
	{
		counter--;
		stopwatch.Restart();
	}
}

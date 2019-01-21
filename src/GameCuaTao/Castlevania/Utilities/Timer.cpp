#include "Timer.h"

using namespace Castlevania;

Timer::Timer(int startingTime)
{
	counter = startingTime;
	stopwatch.Start();
}

void Timer::AddCounter(int counter)
{
	this->counter += counter;
	stopwatch.Restart();
}

void Timer::SetCounter(int counter)
{
	this->counter = counter;
	stopwatch.Restart();
}

void Timer::ResetLastSecond()
{
	SetCounter(counter);
}

int Timer::GetCounter() const
{
	return counter;
}

bool Timer::CountDown()
{
	if (stopwatch.ElapsedMilliseconds() > 1000)
	{
		counter--;
		stopwatch.Restart();
		return true;
	}
	else
		return false;
}

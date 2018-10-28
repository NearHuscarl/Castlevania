#include <ctime>
#include <Windows.h>
#include "Stopwatch.h"

Stopwatch::Stopwatch()
{
	Reset();
}

void Stopwatch::Start()
{
	if (!isRunning)
	{
		isRunning = true;
		startTimeStamp = GetTimeStamp();
	}
}

void Stopwatch::Stop()
{
	if (isRunning)
	{
		auto endTimeStamp = GetTimeStamp();
		auto elapsedThisPeriod = endTimeStamp - startTimeStamp;
		elapsed += elapsedThisPeriod;
		isRunning = false;
	}
}

void Stopwatch::Reset()
{
	elapsed = 0;
	startTimeStamp = 0;
	isRunning = false;
}

bool Stopwatch::IsRunning()
{
	return isRunning;
}

TimeSpan Stopwatch::Elapsed()
{
	return TimeSpan::FromMilliseconds(GetElapsedTime());
}

long Stopwatch::ElapsedMilliseconds()
{
	return GetElapsedTime();
}

long Stopwatch::GetTimeStamp()
{
	//auto currentTimeStamp = system_clock::now().time_since_epoch();
	//return duration_cast<milliseconds>(currentTimeStamp).count();
	return GetTickCount();
}

std::string Stopwatch::GetFomattedTimeStamp(const char *format)
{
	auto timeNow = std::time(nullptr);
	auto timeStruct = *std::localtime(&timeNow);
	char formattedTime[80];

	strftime(formattedTime, sizeof(formattedTime), format, &timeStruct);

	return formattedTime;
}

bool Stopwatch::Every(int interval)
{
	return (GetTimeStamp() / interval) % 2 == 0;
}

bool Stopwatch::Until(int interval)
{
	if (!isRunning)
		Start();

	if (GetElapsedTime() < interval)
		return false;

	Stop();
	return true;
}

long Stopwatch::GetElapsedTime()
{
	auto timeElapsed = elapsed;

	if (isRunning)
	{
		auto currentTimeStamp = GetTimeStamp();
		auto elapsedUntilNow = currentTimeStamp - startTimeStamp;
		timeElapsed += elapsedUntilNow;
	}
	return timeElapsed;
}
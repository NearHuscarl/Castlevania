#include <ctime>
#include <Windows.h>
#include "Stopwatch.h"
#include "FileLogger.h"

double Stopwatch::frequency;
bool Stopwatch::useHighResolutionCounter;

Stopwatch::Stopwatch()
{
	Reset();
}

void Stopwatch::Initialize()
{
	auto result = LARGE_INTEGER{};

	if (!QueryPerformanceFrequency(&result))
	{
		FileLogger::GetInstance().Error("QueryPerformanceFrequency failed");
		useHighResolutionCounter = false;
		return;
	}
	else
	{
		frequency = double(result.QuadPart) / 1000.0;
		useHighResolutionCounter = true;
	}
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

void Stopwatch::Restart()
{
	Reset();
	Start();
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

	if (useHighResolutionCounter)
	{
		auto result = LARGE_INTEGER{};

		QueryPerformanceCounter(&result);
		return result.QuadPart / frequency;
	}
	else
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

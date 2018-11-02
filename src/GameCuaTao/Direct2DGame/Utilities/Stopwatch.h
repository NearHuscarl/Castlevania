#pragma once

#include <string>
#include "TimeSpan.h"

// This class is based on .NET framework's Stopwatch
class Stopwatch
{
public:
	Stopwatch();

	void Start();
	void Stop();
	void Reset();

	bool IsRunning();

	TimeSpan Elapsed();
	long ElapsedMilliseconds();

	static long GetTimeStamp();
	static std::string GetFomattedTimeStamp(const char *format);

	// Flip the boolean flag every <interval> miliseconds
	static bool Every(int interval);

private:
	long elapsed;
	long startTimeStamp;
	bool isRunning;

	long GetElapsedTime();
};
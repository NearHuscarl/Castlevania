#pragma once

#include <string>
#include "TimeSpan.h"

// This class is based on .NET framework's Stopwatch
class Stopwatch
{
public:
	Stopwatch();
	static void Initialize();

	void Start();
	void Stop();
	void Reset();
	void Restart();

	bool IsRunning();

	TimeSpan Elapsed();
	long ElapsedMilliseconds();

	static long GetTimeStamp();
	static std::string GetFomattedTimeStamp(const char *format);

	// Flip the boolean flag every <interval> / 2 miliseconds
	static bool Every(int interval);

private:
	static double frequency;
	static bool useHighResolutionCounter;
	
	long elapsed;
	long startTimeStamp;
	bool isRunning;

	long GetElapsedTime();
};
#pragma once

#include <string>

class TimeHelper
{
public:
	static std::string GetTimeNow(const char *formatter);
	static long GetTickNow();

	// Flip the boolean flag every <interval> miliseconds
	static bool Every(long interval);
};
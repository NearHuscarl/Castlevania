#include <ctime>
#include <Windows.h>
#include "TimeHelper.h"

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

std::string TimeHelper::GetTimeNow(const char *format)
{
	auto timeNow = std::time(nullptr);
	auto timeStruct = *std::localtime(&timeNow);
	char formattedTime[80];

	strftime(formattedTime, sizeof(formattedTime), format, &timeStruct);

	return formattedTime;
}

long TimeHelper::GetTickNow()
{
	return GetTickCount();
}

bool TimeHelper::Every(long interval)
{
	auto tickNow = GetTickCount();

	return (tickNow / interval) % 2 == 0;
}

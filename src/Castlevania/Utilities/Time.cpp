#include <chrono>
#include "Time.h"


/// Get current time in milliseconds since 1970
long Time::GetMiliSeconds()
{
	return std::chrono::steady_clock::now().time_since_epoch().count();
}
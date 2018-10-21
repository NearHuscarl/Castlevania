#pragma once

#include <chrono>

//using Duration = std::chrono::system_clock::duration;
using Duration = std::chrono::duration<long long, std::ratio_multiply<std::hecto, std::pico>>;

class TimeSpan
{
public:
	TimeSpan(Duration duration);

	static const TimeSpan Zero();

	double Nanoseconds();
	double Microseconds();
	double Milliseconds();
	double Seconds();
	double Minutes();
	double Hours();

	static TimeSpan FromNanoseconds(long long value);
	static TimeSpan FromMicroseconds(long long value);
	static TimeSpan FromMilliseconds(long long value);
	static TimeSpan FromSeconds(long long value);
	static TimeSpan FromMinutes(long long value);
	static TimeSpan FromHours(long long value);

	TimeSpan &operator+(const TimeSpan &other);
	TimeSpan &operator+=(const TimeSpan &other);

private:
	static TimeSpan zeroTimeSpan;
	Duration duration;
};
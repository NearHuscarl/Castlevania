#pragma once

#include <chrono>

using Duration = std::chrono::duration<double>; // in seconds

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

	TimeSpan operator+(const TimeSpan &other) const;
	TimeSpan operator+=(const TimeSpan &other);

private:
	Duration duration;
};
#include "TimeSpan.h"

using namespace std::chrono;

TimeSpan::TimeSpan(Duration duration)
{
	this->duration = duration;
}

const TimeSpan TimeSpan::Zero()
{
	static auto zeroTimeSpan = TimeSpan{ Duration::zero() };
	return zeroTimeSpan;
}

double TimeSpan::Nanoseconds()
{
	return (double)duration_cast<nanoseconds>(duration).count();
}

double TimeSpan::Microseconds()
{
	return (double)duration_cast<microseconds>(duration).count();
}

double TimeSpan::Milliseconds()
{
	return (double)duration_cast<milliseconds>(duration).count();
}

double TimeSpan::Seconds()
{
	return duration.count();
}

double TimeSpan::Minutes()
{
	return duration.count() / 60.0;
}

double TimeSpan::Hours()
{
	return duration.count() / 3600.0;
}

TimeSpan TimeSpan::FromNanoseconds(long long value)
{
	auto duration = Duration{ nanoseconds(value) };
	return TimeSpan{ duration };
}

TimeSpan TimeSpan::FromMicroseconds(long long value)
{
	auto duration = Duration{ microseconds(value) };
	return TimeSpan{ duration };
}

TimeSpan TimeSpan::FromMilliseconds(long long value)
{
	auto duration = Duration{ milliseconds(value) };
	return TimeSpan{ duration };
}

TimeSpan TimeSpan::FromSeconds(long long value)
{
	auto duration = Duration{ seconds(value) };
	return TimeSpan{ duration };
}

TimeSpan TimeSpan::FromMinutes(long long value)
{
	auto duration = Duration{ minutes(value) };
	return TimeSpan{ duration };
}

TimeSpan TimeSpan::FromHours(long long value)
{
	auto duration = Duration{ hours(value) };
	return TimeSpan{ duration };
}

TimeSpan TimeSpan::operator+(const TimeSpan &other) const
{
	return TimeSpan{ this->duration + other.duration };
}

TimeSpan TimeSpan::operator+=(const TimeSpan &other)
{
	this->duration += other.duration;
	return *this;
}
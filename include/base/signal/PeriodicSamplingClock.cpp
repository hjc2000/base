#include "PeriodicSamplingClock.h"

void base::PeriodicSamplingClock::AdjustTime()
{
	// 将时间减去整数倍的周期
	int64_t div = static_cast<int64_t>(_current_time / _period);
	_current_time -= _period * div;
}

base::PeriodicSamplingClock::PeriodicSamplingClock(base::unit::Seconds period)
	: _period(period)
{
}

base::PeriodicSamplingClock &base::PeriodicSamplingClock::operator+=(base::unit::Seconds value)
{
	_current_time += value;
	AdjustTime();
	return *this;
}

base::PeriodicSamplingClock &base::PeriodicSamplingClock::operator-=(base::unit::Seconds value)
{
	_current_time -= value;
	AdjustTime();
	return *this;
}

base::unit::Seconds base::PeriodicSamplingClock::Period() const
{
	return _period;
}

base::unit::Seconds base::PeriodicSamplingClock::CurrentTime() const
{
	return _current_time;
}

base::PeriodicSamplingClock::operator base::unit::Seconds() const
{
	return _current_time;
}

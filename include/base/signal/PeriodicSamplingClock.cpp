#include "PeriodicSamplingClock.h"

using namespace base;

void base::PeriodicSamplingClock::AdjustTime()
{
    // 将时间减去整数倍的周期
    int64_t div = static_cast<int64_t>(_time / _period);
    _time -= _period * div;
}

base::PeriodicSamplingClock::PeriodicSamplingClock(base::Fraction period)
    : _period(period)
{
}

PeriodicSamplingClock &base::PeriodicSamplingClock::operator+=(base::Fraction value)
{
    _time += value;
    AdjustTime();
    return *this;
}

PeriodicSamplingClock &base::PeriodicSamplingClock::operator-=(base::Fraction value)
{
    _time -= value;
    AdjustTime();
    return *this;
}

PeriodicSamplingClock &base::PeriodicSamplingClock::operator*=(base::Fraction value)
{
    _time *= value;
    AdjustTime();
    return *this;
}

PeriodicSamplingClock &base::PeriodicSamplingClock::operator/=(base::Fraction value)
{
    _time /= value;
    AdjustTime();
    return *this;
}

base::Fraction base::PeriodicSamplingClock::Period() const
{
    return _period;
}

base::Fraction base::PeriodicSamplingClock::Time() const
{
    return _time;
}

base::PeriodicSamplingClock::operator base::Fraction() const
{
    return _time;
}

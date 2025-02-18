#include "DateTime.h"

base::DateTime::DateTime(base::TimePointSinceEpoch const &time_point)
	: _time_point(time_point)
{
	int64_t remaining = static_cast<std::chrono::nanoseconds>(_time_point - base::TimePointSinceEpoch{}).count();
	{
		// remaining 现在的单位是 ns.

		// 取出纳秒部分
		_nanoseconds_part = remaining % 1000;
		remaining /= 1000;
	}

	{
		// remaining 现在的单位是 us.

		// 取出微秒部分
		_microseconds_part = remaining % 1000;
		remaining /= 1000;
	}

	{
		// remaining 现在的单位是 ms.
		_milliseconds_part = remaining % 1000;
		remaining /= 1000;
	}

	{
		/**
		 * remaining 现在的单位是 s. 这是自 epoch 起点以来的总秒数。
		 * 接下来计算分钟数，需要考虑闰秒。
		 */
	}

	{
		// remaining 现在的单位是 m.
	}

	while (remaining > 0)
	{
	}
}

int64_t base::DateTime::Year() const
{
	return _years_part;
}

int64_t base::DateTime::Month() const
{
	return _months_part;
}

int64_t base::DateTime::Day() const
{
	return _days_part;
}

int64_t base::DateTime::Hour() const
{
	return _hours_part;
}

int64_t base::DateTime::Minutes() const
{
	return _minutes_part;
}

int64_t base::DateTime::Second() const
{
	return _seconds_part;
}

int64_t base::DateTime::Millisecond() const
{
	return _milliseconds_part;
}

int64_t base::DateTime::Microsecond() const
{
	return _microseconds_part;
}

int64_t base::DateTime::Nanosecond() const
{
	return _nanoseconds_part;
}

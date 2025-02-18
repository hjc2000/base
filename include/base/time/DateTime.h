#pragma once
#include <base/time/TimePointSinceEpoch.h>

namespace base
{
	class DateTime
	{
	private:
		/// @brief 本对象日期对应的时间点。
		base::TimePointSinceEpoch const _time_point;

		int64_t _years_part = 1970;
		int64_t _months_part = 1;
		int64_t _days_part = 1;
		int64_t _hours_part = 0;
		int64_t _minutes_part = 0;
		int64_t _seconds_part = 0;
		int64_t _milliseconds_part = 0;
		int64_t _microseconds_part = 0;
		int64_t _nanoseconds_part = 0;

	public:
		DateTime() = default;
		DateTime(base::TimePointSinceEpoch const &time_point);

		int64_t Year() const;
		int64_t Month() const;
		int64_t Day() const;
		int64_t Hour() const;
		int64_t Minutes() const;
		int64_t Second() const;
		int64_t Millisecond() const;
		int64_t Microsecond() const;
		int64_t Nanosecond() const;
	};
} // namespace base

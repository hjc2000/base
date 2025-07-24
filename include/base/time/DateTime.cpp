#include "DateTime.h"
#include "base/string/String.h"
#include "base/time/convert.h"
#include "base/time/time.h"
#include "base/time/TimePointSinceEpoch.h"
#include <array>
#include <bits/chrono.h>
#include <chrono>
#include <cstdint>
#include <cstdlib>

/* #region 不考虑时区转换为本地时区的日期时间字符串 */

base::String base::DateTime::YearString() const
{
	base::String ret{std::to_string(_year)};
	ret.PadLeft('0', base::StringLength{4});
	return ret;
}

base::String base::DateTime::MonthString() const
{
	base::String ret{std::to_string(_month)};
	ret.PadLeft('0', base::StringLength{2});
	return ret;
}

base::String base::DateTime::DayString() const
{
	base::String ret{std::to_string(_day)};
	ret.PadLeft('0', base::StringLength{2});
	return ret;
}

base::String base::DateTime::HourString() const
{
	base::String ret{std::to_string(_hour)};
	ret.PadLeft('0', base::StringLength{2});
	return ret;
}

base::String base::DateTime::MinuteString() const
{
	base::String ret{std::to_string(_minute)};
	ret.PadLeft('0', base::StringLength{2});
	return ret;
}

base::String base::DateTime::SecondString() const
{
	base::String ret{std::to_string(_second)};
	ret.PadLeft('0', base::StringLength{2});
	return ret;
}

base::String base::DateTime::NanosecondString() const
{
	base::String ret{std::to_string(_nanosecond)};
	ret.PadLeft('0', base::StringLength{9});
	return ret;
}

/* #endregion */

/* #region 构造函数 */

base::DateTime::DateTime(base::TimePointSinceEpoch const &time_point)
{
	base::DateTime start{EpochStart()};
	start.AddNanoseconds(static_cast<std::chrono::nanoseconds>(time_point).count());
	*this = start;
}

base::DateTime::DateTime(base::UtcHourOffset utc_hour_offset,
						 base::TimePointSinceEpoch const &time_point)
	: DateTime(time_point)
{
	_utc_hour_offset = utc_hour_offset.Value();
}

/* #endregion */

base::TimePointSinceEpoch base::DateTime::TimePointSinceEpoch() const
{
	std::chrono::nanoseconds total_ns{};
	base::DateTime start{EpochStart()};

	// 把 start 的年份调整到当前年份，累加经过的纳秒数。
	while (true)
	{
		if (start._year == _year)
		{
			break;
		}
		else if (start._year > _year)
		{
			start._year--;
			total_ns -= std::chrono::days{start.CurrentYearDayCount()};
		}
		else if (start._year < _year)
		{
			total_ns += std::chrono::days{start.CurrentYearDayCount()};
			start._year++;
		}
	}

	// 因为 start 是 1 月，所以一定满足 start._month <= _month
	while (start._month < _month)
	{
		total_ns += std::chrono::days{start.CurrentMonthDayCount()};
		start._month++;
	}

	// 因为 start 是 1 日，所以 _day - start._day >= 0
	total_ns += std::chrono::days{_day - start._day};
	total_ns += std::chrono::hours{_hour - 0};
	total_ns += std::chrono::minutes{_minute - 0};
	total_ns += std::chrono::seconds{_second - 0};
	total_ns += std::chrono::nanoseconds{_nanosecond - 0};
	return base::TimePointSinceEpoch{total_ns};
}

base::DateTimeStringBuilder base::DateTime::DateTimeStringBuilder() const
{
	return base::DateTimeStringBuilder{
		YearString().StdString(),
		MonthString().StdString(),
		DayString().StdString(),
		HourString().StdString(),
		MinuteString().StdString(),
		SecondString().StdString(),
		NanosecondString().StdString(),
	};
}

base::DateTimeStringBuilder base::DateTime::LocalDateTimeStringBuilder() const
{
	DateTime copy{*this};
	copy.AddHours(_utc_hour_offset);
	return copy.DateTimeStringBuilder();
}

/* #region 比较 */

bool base::DateTime::operator<(DateTime const &another) const
{
	std::array<int64_t, 7> date_time_array{
		_year,
		_month,
		_day,
		_hour,
		_minute,
		_second,
		_nanosecond,
	};

	std::array<int64_t, 7> another_date_time_array{
		another._year,
		another._month,
		another._day,
		another._hour,
		another._minute,
		another._second,
		another._nanosecond,
	};

	// 利用 std::array 的字典序比较。
	return date_time_array < another_date_time_array;
}

bool base::DateTime::operator>(DateTime const &another) const
{
	std::array<int64_t, 7> date_time_array{
		_year,
		_month,
		_day,
		_hour,
		_minute,
		_second,
		_nanosecond,
	};

	std::array<int64_t, 7> another_date_time_array{
		another._year,
		another._month,
		another._day,
		another._hour,
		another._minute,
		another._second,
		another._nanosecond,
	};

	// 利用 std::array 的字典序比较。
	return date_time_array > another_date_time_array;
}

bool base::DateTime::operator<=(DateTime const &another) const
{
	std::array<int64_t, 7> date_time_array{
		_year,
		_month,
		_day,
		_hour,
		_minute,
		_second,
		_nanosecond,
	};

	std::array<int64_t, 7> another_date_time_array{
		another._year,
		another._month,
		another._day,
		another._hour,
		another._minute,
		another._second,
		another._nanosecond,
	};

	// 利用 std::array 的字典序比较。
	return date_time_array <= another_date_time_array;
}

bool base::DateTime::operator>=(DateTime const &another) const
{
	std::array<int64_t, 7> date_time_array{
		_year,
		_month,
		_day,
		_hour,
		_minute,
		_second,
		_nanosecond,
	};

	std::array<int64_t, 7> another_date_time_array{
		another._year,
		another._month,
		another._day,
		another._hour,
		another._minute,
		another._second,
		another._nanosecond,
	};

	// 利用 std::array 的字典序比较。
	return date_time_array >= another_date_time_array;
}

/* #endregion */

#if HAS_THREAD

void base::test::TestDateTime()
{
	base::TimePointSinceEpoch now_time_point = base::time::Now();

	base::DateTime now{
		base::UtcHourOffset{8},
		now_time_point,
	};

	base::DateTimeStringBuilder dsb = now.LocalDateTimeStringBuilder();
	dsb.SetYearMonthDaySeparator('/');

	std::cout << dsb << std::endl;
	std::cout << base::to_string(now_time_point) << std::endl;
	std::cout << static_cast<std::chrono::nanoseconds>(now_time_point) << std::endl;
	std::cout << static_cast<std::chrono::nanoseconds>(now.TimePointSinceEpoch()) << std::endl;
}

#endif // HAS_THREAD

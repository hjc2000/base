#include "DateTime.h"
#include "base/string/String.h"
#include "base/time/convert.h"
#include "base/time/time.h"
#include "base/time/TimePointSinceEpoch.h"
#include <chrono>
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

#include "DateTime.h"
#include "base/string/define.h"
#include <cstdint>
#include <cstdlib>
#include <stdexcept>

/* #region 检查 */

void base::DateTime::CheckMonth()
{
	if (_month < 1 || _month > 12)
	{
		throw std::invalid_argument{CODE_POS_STR + "非法月份。"};
	}
}

void base::DateTime::CheckDay()
{
	if (_day < 1 || _day > CurrentMonthDayCount())
	{
		throw std::invalid_argument{CODE_POS_STR + "非法日。"};
	}
}

void base::DateTime::CheckHour()
{
	if (_hour < 0 || _hour > 23)
	{
		throw std::invalid_argument{CODE_POS_STR + "非法小时。"};
	}
}

void base::DateTime::CheckMinute()
{
	if (_minute < 0 || _minute > 59)
	{
		throw std::invalid_argument{CODE_POS_STR + "非法分钟。"};
	}
}

void base::DateTime::CheckSecond()
{
	if (_second < 0 || _second > 59)
	{
		throw std::invalid_argument{CODE_POS_STR + "非法秒。"};
	}
}

void base::DateTime::CheckNanosecond()
{
	if (_nanosecond < 0 || _nanosecond > 999)
	{
		throw std::invalid_argument{CODE_POS_STR + "非法纳秒。"};
	}
}

/* #endregion */

/* #region 私有时间调整方法 */

void base::DateTime::AddMonths(int64_t value)
{
	if (value == 0)
	{
		return;
	}

	int64_t month_index = _month - 1 + value;
	if (month_index >= 0 && month_index < 12)
	{
		// 在最小正周期内
		_month = month_index + 1;
		return;
	}

	// 不在最小正周期内
	_year += month_index / 12;
	month_index %= 12;
	if (month_index < 0)
	{
		_year -= 1;
		month_index += 12;
	}

	_month = month_index + 1;
}

void base::DateTime::AdjustDayIndexToOneYear(int64_t &day_index)
{
	if (day_index >= 0 && day_index < CurrentYearDayCount())
	{
		// 以年为周期，已经处于最小正周期内了。
		return;
	}

	if (day_index > 0)
	{
		while (true)
		{
			int64_t current_year_day_count = CurrentYearDayCount();
			if (day_index < current_year_day_count)
			{
				return;
			}

			day_index -= current_year_day_count;
			_year += 1;
		}
	}

	// day_index < 0
	while (true)
	{
		// 前往去年
		_year -= 1;
		day_index += CurrentYearDayCount();
		if (day_index >= 0)
		{
			return;
		}
	}
}

void base::DateTime::AdjustDayIndexToOneMonth(int64_t &day_index)
{
	AdjustDayIndexToOneYear(day_index);

	if (day_index >= 0 && day_index < CurrentMonthDayCount())
	{
		return;
	}

	if (day_index > 0)
	{
		while (true)
		{
			// 对于本月，当前的日的索引是 day_index 的当前值，如果要将索引起点调整到下一个月
			// 的 1 日，即坐标原点向右移动，则 day_index 躺枪，被平白无故变小了。
			//
			// 则 day_index 的值在新的坐标中要减去偏移量 day_index.
			int64_t current_month_day_count = CurrentMonthDayCount();
			if (day_index < current_month_day_count)
			{
				// 到不了下个月
				return;
			}

			day_index -= current_month_day_count;
			AddMonths(1);
		}
	}

	// 到这里说明 day_index < 0
	while (true)
	{
		// 前往上一个月
		AddMonths(-1);
		day_index += CurrentMonthDayCount();
		if (day_index >= 0)
		{
			return;
		}
	}
}

void base::DateTime::AdjustHourIndexToOneDay(int64_t &hour_index)
{
	if (hour_index >= 0 && hour_index < 24)
	{
		return;
	}

	AddDays(hour_index / 24);
	hour_index %= 24;

	if (hour_index < 0)
	{
		AddDays(-1);
		hour_index += 24;
	}
}

void base::DateTime::AdjustMinuteIndexToOneHour(int64_t &minute_index)
{
	if (minute_index >= 0 && minute_index < 60)
	{
		return;
	}

	AddHours(minute_index / 60);
	minute_index %= 60;
	if (minute_index < 0)
	{
		AddHours(-1);
		minute_index += 60;
	}
}

void base::DateTime::AdjustSecondsIndexToOneMinute(int64_t &second_index)
{
	if (second_index >= 0 && second_index < 60)
	{
		return;
	}

	AddMinutes(second_index / 60);
	second_index %= 60;
	if (second_index < 0)
	{
		AddMinutes(-1);
		second_index += 60;
	}
}

/* #endregion */

/* #region 构造函数 */

base::DateTime::DateTime(int64_t year, int64_t month, int64_t day,
						 int64_t hour, int64_t minute, int64_t second,
						 int64_t nanosecond)
{
	_year = year;
	_month = month;
	_day = day;
	_hour = hour;
	_minute = minute;
	_second = second;
	_nanosecond = nanosecond;

	CheckMonth();
	CheckDay();
	CheckHour();
	CheckMinute();
	CheckSecond();
	CheckNanosecond();
}

base::DateTime::DateTime(base::UtcHourOffset utc_hour_offset,
						 int64_t year, int64_t month, int64_t day,
						 int64_t hour, int64_t minute, int64_t second,
						 int64_t nanosecond)
	: DateTime(year, month, day,
			   hour, minute, second, nanosecond)
{
	_utc_hour_offset = utc_hour_offset.Value();

	// 调整回 UTC + 0 时间。
	// 因为本类的字段储存的始终是 UTC + 0 时间。
	AddHours(-_utc_hour_offset);
}

/* #endregion */

int64_t base::DateTime::CurrentYearDayCount()
{
	if (IsLeapYear())
	{
		return 366;
	}

	return 365;
}

int64_t base::DateTime::CurrentMonthDayCount()
{
	switch (_month)
	{
	case 2:
		{
			if (IsLeapYear())
			{
				return 29;
			}

			return 28;
		}
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		{
			return 31;
		}
	default:
		{
			return 30;
		}
	}
}

bool base::DateTime::IsLeapYear() const
{
	if (_year % 100 == 0)
	{
		// 整百年份必须被 400 整除才是闰年。
		return _year % 400 == 0;
	}

	// 非整百年份只要能被 4 整除就是闰年。
	return _year % 4 == 0;
}

/* #region 公共时间调整方法 */

void base::DateTime::AddDays(int64_t value)
{
	if (value == 0)
	{
		return;
	}

	// 以本月 1 日为 0 索引，建立日的索引。
	int64_t day_index = _day - 1 + value;
	AdjustDayIndexToOneMonth(day_index);
	_day = day_index + 1;
}

void base::DateTime::AddHours(int64_t value)
{
	_hour += value;
	AdjustHourIndexToOneDay(_hour);
}

void base::DateTime::AddMinutes(int64_t value)
{
	_minute += value;
	AdjustMinuteIndexToOneHour(_minute);
}

void base::DateTime::AddSeconds(int64_t value)
{
	_second += value;
	AdjustSecondsIndexToOneMinute(_second);
}

/* #endregion */

std::string base::DateTime::ToString() const
{
	DateTime copy{*this};
	copy.AddHours(_utc_hour_offset);

	std::string ret{};
	ret += std::to_string(copy._year) + '-';
	ret += std::to_string(copy._month) + '-';
	ret += std::to_string(copy._day);
	ret += ' ';
	ret += std::to_string(copy._hour) + ':';
	ret += std::to_string(copy._minute) + ':';
	ret += std::to_string(copy._second);
	ret += '.';
	ret += std::to_string(copy._nanosecond);
	return ret;
}

/* #region 比较 */

bool base::DateTime::operator==(DateTime const &another) const
{
	return _year == another._year &&
		   _month == another._month &&
		   _day == another._day &&
		   _hour == another._hour &&
		   _minute == another._minute &&
		   _second == another._second &&
		   _nanosecond == another._nanosecond;
}

bool base::DateTime::operator<(DateTime const &another) const
{
	if (_year < another._year)
	{
		return true;
	}

	if (_year > another._year)
	{
		return false;
	}

	if (_month < another._month)
	{
		return true;
	}

	if (_month > another._month)
	{
		return false;
	}

	if (_day < another._day)
	{
		return true;
	}

	if (_day > another._day)
	{
		return false;
	}

	if (_hour < another._hour)
	{
		return true;
	}

	if (_hour > another._hour)
	{
		return false;
	}

	if (_minute < another._minute)
	{
		return true;
	}

	if (_minute > another._minute)
	{
		return false;
	}

	if (_second < another._second)
	{
		return true;
	}

	if (_second > another._second)
	{
		return false;
	}

	return _nanosecond < another._nanosecond;
}

bool base::DateTime::operator>(DateTime const &another) const
{
	if (*this == another)
	{
		return false;
	}

	if (*this < another)
	{
		return false;
	}

	return true;
}

bool base::DateTime::operator<=(DateTime const &another) const
{
	if (*this == another)
	{
		return true;
	}

	return *this < another;
}

bool base::DateTime::operator>=(DateTime const &another) const
{
	if (*this == another)
	{
		return true;
	}

	return *this > another;
}

/* #endregion */

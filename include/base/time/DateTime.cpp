#include "DateTime.h"
#include "base/string/define.h"
#include <cstdint>
#include <cstdlib>
#include <map>
#include <stdexcept>

namespace
{
	/* #region PrivateDateTime */

	class PrivateDateTime
	{
	private:
		int64_t _year{};
		int64_t _month{};

	public:
		PrivateDateTime() = default;

		PrivateDateTime(int64_t year, int64_t month)
		{
			_year = year;
			_month = month;
		}

		/* #region 属性 */

		int64_t Year() const
		{
			return _year;
		}

		int64_t Month() const
		{
			return _month;
		}

		/* #endregion */

		/* #region 比较 */

		bool operator==(PrivateDateTime const &another) const
		{
			return _year == another._year &&
				   _month == another._month;
		}

		bool operator<(PrivateDateTime const &another) const
		{
			if (_year < another._year)
			{
				return true;
			}

			if (_year > another._year)
			{
				return false;
			}

			return _month < another._month;
		}

		bool operator>(PrivateDateTime const &another) const
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

		bool operator<=(PrivateDateTime const &another) const
		{
			if (*this == another)
			{
				return true;
			}

			return *this < another;
		}

		bool operator>=(PrivateDateTime const &another) const
		{
			if (*this == another)
			{
				return true;
			}

			return *this > another;
		}

		/* #endregion */
	};

	/* #endregion */

	///
	/// @brief UTC+0 的闰秒表。
	///
	///
	std::map<PrivateDateTime, int64_t> _leap_second_map{
		{PrivateDateTime{1972, 6}, 1},
		{PrivateDateTime{1972, 12}, 1},
		{PrivateDateTime{1973, 12}, 1},
		{PrivateDateTime{1974, 12}, 1},
		{PrivateDateTime{1975, 12}, 1},
		{PrivateDateTime{1976, 12}, 1},
		{PrivateDateTime{1977, 12}, 1},
		{PrivateDateTime{1978, 12}, 1},
		{PrivateDateTime{1979, 12}, 1},
		{PrivateDateTime{1981, 6}, 1},
		{PrivateDateTime{1982, 6}, 1},
		{PrivateDateTime{1983, 6}, 1},
		{PrivateDateTime{1985, 6}, 1},
		{PrivateDateTime{1987, 12}, 1},
		{PrivateDateTime{1989, 12}, 1},
		{PrivateDateTime{1990, 12}, 1},
		{PrivateDateTime{1992, 6}, 1},
		{PrivateDateTime{1993, 6}, 1},
		{PrivateDateTime{1994, 6}, 1},
		{PrivateDateTime{1995, 12}, 1},
		{PrivateDateTime{1997, 6}, 1},
		{PrivateDateTime{1998, 12}, 1},
		{PrivateDateTime{2005, 12}, 1},
		{PrivateDateTime{2008, 12}, 1},
		{PrivateDateTime{2012, 6}, 1},
		{PrivateDateTime{2015, 6}, 1},
		{PrivateDateTime{2016, 12}, 1},
	};

} // namespace

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
	if (_second < 0 || _second > 59 + LeapSecond())
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

void base::DateTime::AddMonths(int64_t value)
{
	if (value == 0)
	{
		return;
	}

	int64_t month_index = _month - 1 + value;
	if (std::abs(month_index) < 12)
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
	if (day_index >= 0 && day_index < 365)
	{
		// 以年为周期，已经处于最小正周期内了。
		return;
	}

	if (day_index > 0)
	{
		while (true)
		{
			if (IsLeapYear())
			{
				// 是闰年
				if (day_index < 366)
				{
					return;
				}

				day_index -= 366;
				_year += 1;
			}
			else
			{
				// 是平年
				if (day_index < 365)
				{
					return;
				}

				day_index -= 365;
				_year += 1;
			}
		}
	}

	// day_index < 0
	while (true)
	{
		// 前往去年
		_year -= 1;
		if (IsLeapYear())
		{
			// 去年是闰年
			day_index += 366;
		}
		else
		{
			// 去年是平年
			day_index += 365;
		}

		if (day_index >= 0)
		{
			return;
		}
	}
}

void base::DateTime::AdjustDayIndexToOneMonth(int64_t &day_index)
{
	AdjustDayIndexToOneYear(day_index);

	if (day_index >= 0 && day_index < 28)
	{
		// 以月为周期，已经处于最小正周期内了。
		// 即使周期来到最小的平年 2 月，也能够满足处于一个最小正周期内。
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
			int64_t delta = CurrentMonthDayCount();
			if (day_index < delta)
			{
				// 到不了下个月
				return;
			}

			day_index -= delta;
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

base::DateTime base::DateTime::CreateWithoutCheck(int64_t year, int64_t month, int64_t day,
												  int64_t hour, int64_t minute, int64_t second,
												  int64_t nanosecond)
{
	base::DateTime ret{};
	ret._year = year;
	ret._month = month;
	ret._day = day;
	ret._hour = hour;
	ret._minute = minute;
	ret._second = second;
	ret._nanosecond = nanosecond;
	return ret;
}

int64_t base::DateTime::CountLeapSeconds(base::DateTime const &start, base::DateTime const &end)
{
	int64_t total_leap_second = 0;

	for (auto private_date_time_pair : _leap_second_map)
	{
		base::DateTime leap_second_date_time;

		{
			PrivateDateTime const &private_date_time = private_date_time_pair.first;
			int64_t leap_second = private_date_time_pair.second;

			int64_t day = 31;
			if (private_date_time.Month() == 6)
			{
				day = 30;
			}

			leap_second_date_time = CreateWithoutCheck(private_date_time.Year(),
													   private_date_time.Month(),
													   day,
													   23,
													   59,
													   59 + leap_second,
													   0);
		}
	}

	return total_leap_second;
}

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

	throw std::invalid_argument{CODE_POS_STR + "非法月份。"};
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

int64_t base::DateTime::LeapSecond() const
{
	if (_year < 1972 || _year > 2016)
	{
		// 1972 年以前没有闰秒。
		// 目前 2016 年以后没有闰秒。
		return 0;
	}

	if (_month != 6 && _month != 12)
	{
		// 只会在 6 月或 12 月添加闰秒。
		return 0;
	}

	if (_month == 6 && _day != 30)
	{
		// 6 月份必定在 30 日添加闰秒。
		return 0;
	}

	if (_month == 12 && _day != 31)
	{
		// 12 月份必定在 31 日添加闰秒。
		return 0;
	}

	if (_hour != 23)
	{
		return 0;
	}

	if (_minute != 59)
	{
		return 0;
	}

	// 开始查表
	auto it = _leap_second_map.find(PrivateDateTime{_year, _month});
	if (it != _leap_second_map.end())
	{
		return it->second;
	}

	return 0;
}

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

std::string base::DateTime::ToString() const
{
	std::string ret{};
	ret += std::to_string(_year) + '-';
	ret += std::to_string(_month) + '-';
	ret += std::to_string(_day);
	ret += ' ';
	ret += std::to_string(_hour) + ':';
	ret += std::to_string(_minute) + ':';
	ret += std::to_string(_second);
	ret += '.';
	ret += std::to_string(_nanosecond);
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

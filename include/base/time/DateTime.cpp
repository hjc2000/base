#include "DateTime.h"
#include "base/string/define.h"
#include <cstdint>
#include <map>
#include <stdexcept>

namespace
{
	/* #region YearMonth */

	class YearMonth
	{
	private:
		int64_t _year{};
		int64_t _month{};

	public:
		YearMonth() = default;

		YearMonth(int64_t year, int64_t month)
			: _year(year),
			  _month(month)
		{
		}

		int64_t Year() const
		{
			return _year;
		}

		int64_t Month() const
		{
			return _month;
		}

		bool operator==(YearMonth const &another) const
		{
			return _year == another._year &&
				   _month == another._month;
		}

		bool operator<(YearMonth const &another) const
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

		bool operator>(YearMonth const &another) const
		{
			if (_year > another._year)
			{
				return true;
			}

			if (_year < another._year)
			{
				return false;
			}

			return _month > another._month;
		}

		bool operator<=(YearMonth const &another) const
		{
			if (*this == another)
			{
				return true;
			}

			return *this < another;
		}

		bool operator>=(YearMonth const &another) const
		{
			if (*this == another)
			{
				return true;
			}

			return *this > another;
		}
	};

	/* #endregion */

	///
	/// @brief UTC+0 的闰秒表。
	///
	///
	std::map<YearMonth, base::LeapSecondState> _leap_second_years{
		{YearMonth{1972, 6}, base::LeapSecondState::AddOneSecond},
		{YearMonth{1972, 12}, base::LeapSecondState::AddOneSecond},
		{YearMonth{1973, 12}, base::LeapSecondState::AddOneSecond},
		{YearMonth{1974, 12}, base::LeapSecondState::AddOneSecond},
		{YearMonth{1975, 12}, base::LeapSecondState::AddOneSecond},
		{YearMonth{1976, 12}, base::LeapSecondState::AddOneSecond},
		{YearMonth{1977, 12}, base::LeapSecondState::AddOneSecond},
		{YearMonth{1978, 12}, base::LeapSecondState::AddOneSecond},
		{YearMonth{1979, 12}, base::LeapSecondState::AddOneSecond},
		{YearMonth{1981, 6}, base::LeapSecondState::AddOneSecond},
		{YearMonth{1982, 6}, base::LeapSecondState::AddOneSecond},
		{YearMonth{1983, 6}, base::LeapSecondState::AddOneSecond},
		{YearMonth{1985, 6}, base::LeapSecondState::AddOneSecond},
		{YearMonth{1987, 12}, base::LeapSecondState::AddOneSecond},
		{YearMonth{1989, 12}, base::LeapSecondState::AddOneSecond},
		{YearMonth{1990, 12}, base::LeapSecondState::AddOneSecond},
		{YearMonth{1992, 6}, base::LeapSecondState::AddOneSecond},
		{YearMonth{1993, 6}, base::LeapSecondState::AddOneSecond},
		{YearMonth{1994, 6}, base::LeapSecondState::AddOneSecond},
		{YearMonth{1995, 12}, base::LeapSecondState::AddOneSecond},
		{YearMonth{1997, 6}, base::LeapSecondState::AddOneSecond},
		{YearMonth{1998, 12}, base::LeapSecondState::AddOneSecond},
		{YearMonth{2005, 12}, base::LeapSecondState::AddOneSecond},
		{YearMonth{2008, 12}, base::LeapSecondState::AddOneSecond},
		{YearMonth{2012, 6}, base::LeapSecondState::AddOneSecond},
		{YearMonth{2015, 6}, base::LeapSecondState::AddOneSecond},
		{YearMonth{2016, 12}, base::LeapSecondState::AddOneSecond},
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
	if (_day < 1)
	{
		throw std::invalid_argument{CODE_POS_STR + "非法日。"};
	}

	switch (_month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		{
			if (_day > 31)
			{
				throw std::invalid_argument{CODE_POS_STR + "非法日。"};
			}

			break;
		}
	case 4:
	case 6:
	case 9:
	case 11:
		{
			if (_day > 30)
			{
				throw std::invalid_argument{CODE_POS_STR + "非法日。"};
			}

			break;
		}
	case 2:
		{
			if (IsLeapYear())
			{
				if (_day > 29)
				{
					throw std::invalid_argument{CODE_POS_STR + "非法日。"};
				}
			}
			else
			{
				if (_day > 28)
				{
					throw std::invalid_argument{CODE_POS_STR + "非法日。"};
				}
			}

			break;
		}
	default:
		{
			throw std::invalid_argument{CODE_POS_STR + "非法月份。"};
		}
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
	if (_second < 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "非法秒。"};
	}

	// 需要根据是否闰秒来判断秒的上界
	switch (LeapSecondState())
	{
	case base::LeapSecondState::None:
		{
			if (_second > 59)
			{
				throw std::invalid_argument{CODE_POS_STR + "非法秒。"};
			}

			break;
		}
	case base::LeapSecondState::AddOneSecond:
		{
			if (_second > 60)
			{
				throw std::invalid_argument{CODE_POS_STR + "非法秒。"};
			}

			break;
		}
	default:
		{
			if (_second > 58)
			{
				throw std::invalid_argument{CODE_POS_STR + "非法秒。"};
			}

			break;
		}
	}
}

void base::DateTime::CheckNanosecond()
{
	if (_nanosecond < 0 || _nanosecond > 999)
	{
		throw std::invalid_argument{CODE_POS_STR + "非法纳秒。"};
	}
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

base::LeapSecondState base::DateTime::LeapSecondState() const
{
	if (_year < 1972 || _year > 2016)
	{
		// 1972 年以前没有闰秒。
		// 目前 2016 年以后没有闰秒。
		return base::LeapSecondState::None;
	}

	if (_month != 6 && _month != 12)
	{
		// 只会在 6 月或 12 月添加闰秒。
		return base::LeapSecondState::None;
	}

	if (_month == 6 && _day != 30)
	{
		// 6 月份必定在 30 日添加闰秒。
		return base::LeapSecondState::None;
	}

	if (_month == 12 && _day != 31)
	{
		// 12 月份必定在 31 日添加闰秒。
		return base::LeapSecondState::None;
	}

	if (_hour != 23)
	{
		return base::LeapSecondState::None;
	}

	if (_minute != 59)
	{
		return base::LeapSecondState::None;
	}

	// 开始查表
	auto it = _leap_second_years.find(YearMonth{_year, _month});
	if (it != _leap_second_years.end())
	{
		return it->second;
	}

	return base::LeapSecondState::None;
}

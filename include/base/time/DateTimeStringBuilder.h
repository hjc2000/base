#pragma once
#include "base/string/ICanToString.h"
#include <string>

namespace base
{
	///
	/// @brief 日期时间字符串构建器。
	///
	class DateTimeStringBuilder :
		public base::ICanToString
	{
	public:
		///
		/// @brief 位于秒后面的高分辨率时间的显示选项。
		///
		enum class HighResolutionDisplayOptionEnum
		{
			DisplayNone,
			DisplayMillisecond,
			DisplayMicrosecond,
			DisplayNanosecond,
		};

	private:
		std::string _year;
		std::string _month;
		std::string _day;
		std::string _hour;
		std::string _minute;
		std::string _second;
		std::string _millisecond;
		std::string _microsecond;
		std::string _nanosecond;

		char _year_month_day_separator = '-';

		base::DateTimeStringBuilder::HighResolutionDisplayOptionEnum _display_option = base::DateTimeStringBuilder::HighResolutionDisplayOptionEnum::DisplayNanosecond;

	public:
		///
		/// @brief 通过日期时间的各部分的字符串构造日期时间字符串。
		///
		/// @param year 年字符串。
		/// @param month 月字符串。
		/// @param day 日字符串。
		/// @param hour 小时字符串。
		/// @param minute 分钟字符串。
		/// @param second 秒字符串。
		/// @param millisecond 豪秒字符串。
		/// @param microsecond 微秒字符串。
		/// @param nanosecond 纳秒字符串。
		///
		DateTimeStringBuilder(std::string const &year,
							  std::string const &month,
							  std::string const &day,
							  std::string const &hour,
							  std::string const &minute,
							  std::string const &second,
							  std::string const &millisecond,
							  std::string const &microsecond,
							  std::string const &nanosecond)
			: _year(year),
			  _month(month),
			  _day(day),
			  _hour(hour),
			  _minute(minute),
			  _second(second),
			  _millisecond(millisecond),
			  _microsecond(microsecond),
			  _nanosecond(nanosecond)
		{
		}

		/* #region 日期时间的各部分字符串 */

		std::string Year() const
		{
			return _year;
		}

		std::string Month() const
		{
			return _month;
		}

		std::string Day() const
		{
			return _day;
		}

		std::string Hour() const
		{
			return _hour;
		}

		std::string Minute() const
		{
			return _minute;
		}

		std::string Second() const
		{
			return _second;
		}

		std::string Nanosecond() const
		{
			return _nanosecond;
		}

		///
		/// @brief 年月日字符串。
		///
		/// @return
		///
		std::string YearMonthDay() const
		{
			return Year() + _year_month_day_separator +
				   Month() + _year_month_day_separator +
				   Day();
		}

		///
		/// @brief 时分秒字符串。
		///
		/// @return
		///
		std::string HourMinuteSecond() const
		{
			return Hour() + ':' +
				   Minute() + ':' +
				   Second();
		}

		/* #endregion */

		///
		/// @brief 转化为字符串。
		///
		/// @return
		///
		virtual std::string ToString() const override
		{
			std::string ret = _year + _year_month_day_separator +
							  _month + _year_month_day_separator +
							  _day +
							  ' ' +
							  _hour + ":" +
							  _minute + ':' +
							  _second;

			switch (_display_option)
			{
			default:
			case base::DateTimeStringBuilder::HighResolutionDisplayOptionEnum::DisplayNone:
				{
					break;
				}
			case base::DateTimeStringBuilder::HighResolutionDisplayOptionEnum::DisplayMillisecond:
				{
					ret += '.' + _millisecond;
					break;
				}
			case base::DateTimeStringBuilder::HighResolutionDisplayOptionEnum::DisplayMicrosecond:
				{
					ret += '.' + _microsecond;
					break;
				}
			case base::DateTimeStringBuilder::HighResolutionDisplayOptionEnum::DisplayNanosecond:
				{
					ret += '.' + _nanosecond;
					break;
				}
			}

			return ret;
		}

		///
		/// @brief 年月日分隔符。
		///
		/// @return
		///
		char YearMonthDaySeparator() const
		{
			return _year_month_day_separator;
		}

		///
		/// @brief 设置年月日分隔符。
		///
		/// @param value
		///
		void SetYearMonthDaySeparator(char value)
		{
			_year_month_day_separator = value;
		}

		///
		/// @brief 高分辨率时间显示选项。
		///
		/// @return
		///
		base::DateTimeStringBuilder::HighResolutionDisplayOptionEnum HighResolutionDisplayOption() const
		{
			return _display_option;
		}

		///
		/// @brief 设置高分辨率时间显示选项。
		///
		/// @param value
		///
		void SetHighResolutionDisplayOption(base::DateTimeStringBuilder::HighResolutionDisplayOptionEnum value)
		{
			_display_option = value;
		}
	};

} // namespace base

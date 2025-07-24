#pragma once
#include "base/string/ICanToString.h"
#include <string>

namespace base
{
	///
	/// @brief 日期时间字符串构建器。
	///
	///
	class DateTimeStringBuilder :
		public base::ICanToString
	{
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

		bool _display_nanosecond = true;

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
							  std::string const &nanosecond);

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
		/// @return std::string
		///
		std::string YearMonthDay() const;

		///
		/// @brief 时分秒字符串。
		///
		/// @return std::string
		///
		std::string HourMinuteSecond() const;

		/* #endregion */

		///
		/// @brief 转化为字符串。
		///
		/// @return std::string
		///
		virtual std::string ToString() const override;

		///
		/// @brief 年月日分隔符。
		///
		/// @return char
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
		/// @brief 格式化输出的字符串是否显示纳秒。
		///
		/// @param display
		///
		void DisplayNanosecond(bool display)
		{
			_display_nanosecond = display;
		}
	};

} // namespace base

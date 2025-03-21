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
		std::string _nanosecond;

		char _year_separator = '-';

		bool _display_nanosecond = true;

	public:
		DateTimeStringBuilder(std::string const &year,
							  std::string const &month,
							  std::string const &day,
							  std::string const &hour,
							  std::string const &minute,
							  std::string const &second,
							  std::string const &nanosecond);

		/* #region 获取各部分字符串引用 */

		std::string &Year()
		{
			return _year;
		}

		std::string &Month()
		{
			return _month;
		}

		std::string &Day()
		{
			return _day;
		}

		std::string &Hour()
		{
			return _hour;
		}

		std::string &Minute()
		{
			return _minute;
		}

		std::string &Second()
		{
			return _second;
		}

		std::string &Nanosecond()
		{
			return _nanosecond;
		}

		/* #endregion */

		/* #region 获取各部分字符串 const 引用 */

		std::string const &Year() const
		{
			return _year;
		}

		std::string const &Month() const
		{
			return _month;
		}

		std::string const &Day() const
		{
			return _day;
		}

		std::string const &Hour() const
		{
			return _hour;
		}

		std::string const &Minute() const
		{
			return _minute;
		}

		std::string const &Second() const
		{
			return _second;
		}

		std::string const &Nanosecond() const
		{
			return _nanosecond;
		}

		/* #endregion */

		///
		/// @brief 转化为字符串。
		///
		/// @return std::string
		///
		virtual std::string ToString() const override;

		char YearSeparator() const
		{
			return _year_separator;
		}

		void SetYearSeparator(char value)
		{
			_year_separator = value;
		}

		void DisplayNanosecond(bool display)
		{
			_display_nanosecond = display;
		}
	};

} // namespace base

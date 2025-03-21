#pragma once
#include "base/string/ICanToString.h"
#include <string>

namespace base
{
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

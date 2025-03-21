#include "DateTimeStringBuilder.h"

base::DateTimeStringBuilder::DateTimeStringBuilder(std::string const &year,
												   std::string const &month,
												   std::string const &day,
												   std::string const &hour,
												   std::string const &minute,
												   std::string const &second,
												   std::string const &nanosecond)
	: _year(year),
	  _month(month),
	  _day(day),
	  _hour(hour),
	  _minute(minute),
	  _second(second),
	  _nanosecond(nanosecond)
{
}

std::string base::DateTimeStringBuilder::ToString() const
{
	std::string ret = _year + _year_separator + _month + _year_separator + _day +
					  ' ' +
					  _hour + ":" + _minute + ':' + _second;

	if (_display_nanosecond)
	{
		ret += '.' + _nanosecond;
	}

	return ret;
}

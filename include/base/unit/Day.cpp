#include "base/unit/Hours.h"
#include "base/unit/Nanoseconds.h"
#include "Day.h"


/* #region 构造函数 */

base::Day::Day(base::Fraction const &value)
{
	_value = value;
}

base::Day::Day(base::Hours const &value)
{
	_value = static_cast<base::Fraction>(value) / 24;
}

base::Day::Day(base::Minutes const &value)
	: Day(base::Hours{value})
{
}

base::Day::Day(base::Seconds const &value)
	: Day(base::Hours{value})
{
}

base::Day::Day(base::Nanoseconds const &value)
	: Day(base::Hours{value})
{
}

base::Day::Day(base::Hz const &value)
	: Day(base::Hours{value})
{
}

base::Day::Day(base::MHz const &value)
	: Day(base::Hours{value})
{
}

base::Day::Day(std::chrono::seconds const &value)
	: Day(base::Hours{value})
{
}

base::Day::Day(std::chrono::milliseconds const &value)
	: Day(base::Hours{value})
{
}

base::Day::Day(std::chrono::microseconds const &value)
	: Day(base::Hours{value})
{
}

base::Day::Day(std::chrono::nanoseconds const &value)
	: Day(base::Nanoseconds{value})
{
}

/* #endregion */

base::Fraction &base::Day::Value()
{
	return _value;
}

std::string base::Day::UnitString() const
{
	return "d";
}

/* #region 强制转换运算符 */

base::Day::operator std::chrono::days() const
{
	return std::chrono::days{base::Hours{*this}};
}

base::Day::operator std::chrono::hours() const
{
	return std::chrono::hours{base::Hours{*this}};
}

base::Day::operator std::chrono::minutes() const
{
	return std::chrono::minutes{base::Hours{*this}};
}

base::Day::operator std::chrono::seconds() const
{
	return std::chrono::seconds{base::Hours{*this}};
}

base::Day::operator std::chrono::milliseconds() const
{
	return std::chrono::milliseconds{base::Hours{*this}};
}

base::Day::operator std::chrono::microseconds() const
{
	return std::chrono::microseconds{base::Hours{*this}};
}

base::Day::operator std::chrono::nanoseconds() const
{
	return std::chrono::nanoseconds{base::Hours{*this}};
}

/* #endregion */

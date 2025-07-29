#include "Day.h"
#include "base/unit/Hours.h"
#include "base/unit/Nanoseconds.h"

/* #region 构造函数 */

base::unit::Day::Day(base::Fraction const &value)
{
	_value = value;
}

base::unit::Day::Day(base::unit::Hours const &value)
{
	_value = static_cast<base::Fraction>(value) / 24;
}

base::unit::Day::Day(base::unit::Minutes const &value)
	: Day(base::unit::Hours{value})
{
}

base::unit::Day::Day(base::unit::Seconds const &value)
	: Day(base::unit::Hours{value})
{
}

base::unit::Day::Day(base::unit::Nanoseconds const &value)
	: Day(base::unit::Hours{value})
{
}

base::unit::Day::Day(base::unit::Hz const &value)
	: Day(base::unit::Hours{value})
{
}

base::unit::Day::Day(base::unit::MHz const &value)
	: Day(base::unit::Hours{value})
{
}

base::unit::Day::Day(std::chrono::seconds const &value)
	: Day(base::unit::Hours{value})
{
}

base::unit::Day::Day(std::chrono::milliseconds const &value)
	: Day(base::unit::Hours{value})
{
}

base::unit::Day::Day(std::chrono::microseconds const &value)
	: Day(base::unit::Hours{value})
{
}

base::unit::Day::Day(std::chrono::nanoseconds const &value)
	: Day(base::unit::Nanoseconds{value})
{
}

/* #endregion */

base::Fraction &base::unit::Day::Value()
{
	return _value;
}

std::string base::unit::Day::UnitString() const
{
	return "d";
}

/* #region 强制转换运算符 */

base::unit::Day::operator std::chrono::days() const
{
	return std::chrono::days{base::unit::Hours{*this}};
}

base::unit::Day::operator std::chrono::hours() const
{
	return std::chrono::hours{base::unit::Hours{*this}};
}

base::unit::Day::operator std::chrono::minutes() const
{
	return std::chrono::minutes{base::unit::Hours{*this}};
}

base::unit::Day::operator std::chrono::seconds() const
{
	return std::chrono::seconds{base::unit::Hours{*this}};
}

base::unit::Day::operator std::chrono::milliseconds() const
{
	return std::chrono::milliseconds{base::unit::Hours{*this}};
}

base::unit::Day::operator std::chrono::microseconds() const
{
	return std::chrono::microseconds{base::unit::Hours{*this}};
}

base::unit::Day::operator std::chrono::nanoseconds() const
{
	return std::chrono::nanoseconds{base::unit::Hours{*this}};
}

/* #endregion */

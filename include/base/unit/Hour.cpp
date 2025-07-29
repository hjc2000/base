#include "base/unit/Day.h"
#include "base/unit/Minutes.h"
#include "Hour.h"
#include "Nanoseconds.h"


/* #region 构造函数 */

base::unit::Hour::Hour(base::Fraction const &value)
{
	_value = value;
}

base::unit::Hour::Hour(base::unit::Day const &value)
{
	_value = static_cast<base::Fraction>(value) * 24;
}

base::unit::Hour::Hour(base::unit::Minutes const &value)
{
	_value = static_cast<base::Fraction>(value) / 60;
}

base::unit::Hour::Hour(base::unit::Seconds const &value)
	: Hour(base::unit::Minutes{value})
{
}

base::unit::Hour::Hour(base::unit::Nanoseconds const &value)
	: Hour(base::unit::Minutes{value})
{
}

base::unit::Hour::Hour(base::unit::Hz const &value)
	: Hour(base::unit::Minutes{value})
{
}

base::unit::Hour::Hour(base::unit::MHz const &value)
	: Hour(base::unit::Minutes{value})
{
}

base::unit::Hour::Hour(std::chrono::seconds const &value)
	: Hour(base::unit::Minutes{value})
{
}

base::unit::Hour::Hour(std::chrono::milliseconds const &value)
	: Hour(base::unit::Minutes{value})
{
}

base::unit::Hour::Hour(std::chrono::microseconds const &value)
	: Hour(base::unit::Minutes{value})
{
}

base::unit::Hour::Hour(std::chrono::nanoseconds const &value)
	: base::unit::Hour(base::unit::Nanoseconds{value})
{
}

/* #endregion */

base::Fraction &base::unit::Hour::Value()
{
	return _value;
}

std::string base::unit::Hour::UnitString() const
{
	return "h";
}

/* #region 强制转换运算符 */

base::unit::Hour::operator std::chrono::days() const
{
	return std::chrono::days{base::unit::Minutes{*this}};
}

base::unit::Hour::operator std::chrono::hours() const
{
	return std::chrono::hours{base::unit::Minutes{*this}};
}

base::unit::Hour::operator std::chrono::minutes() const
{
	return std::chrono::minutes{base::unit::Minutes{*this}};
}

base::unit::Hour::operator std::chrono::seconds() const
{
	return std::chrono::seconds{base::unit::Minutes{*this}};
}

base::unit::Hour::operator std::chrono::milliseconds() const
{
	return std::chrono::milliseconds{base::unit::Minutes{*this}};
}

base::unit::Hour::operator std::chrono::microseconds() const
{
	return std::chrono::microseconds{base::unit::Minutes{*this}};
}

base::unit::Hour::operator std::chrono::nanoseconds() const
{
	return std::chrono::nanoseconds{base::unit::Minutes{*this}};
}

/* #endregion */

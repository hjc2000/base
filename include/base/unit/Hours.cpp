#include "Hours.h"
#include "base/unit/Day.h"
#include "base/unit/Minutes.h"
#include "Nanoseconds.h"

/* #region 构造函数 */

base::unit::Hours::Hours(base::Fraction const &value)
{
	_value = value;
}

base::unit::Hours::Hours(base::unit::Day const &value)
{
	_value = static_cast<base::Fraction>(value) * 24;
}

base::unit::Hours::Hours(base::unit::Minutes const &value)
{
	_value = static_cast<base::Fraction>(value) / 60;
}

base::unit::Hours::Hours(base::unit::Seconds const &value)
	: Hours(base::unit::Minutes{value})
{
}

base::unit::Hours::Hours(base::unit::Nanoseconds const &value)
	: Hours(base::unit::Minutes{value})
{
}

base::unit::Hours::Hours(base::unit::Hz const &value)
	: Hours(base::unit::Minutes{value})
{
}

base::unit::Hours::Hours(base::unit::MHz const &value)
	: Hours(base::unit::Minutes{value})
{
}

base::unit::Hours::Hours(std::chrono::seconds const &value)
	: Hours(base::unit::Minutes{value})
{
}

base::unit::Hours::Hours(std::chrono::milliseconds const &value)
	: Hours(base::unit::Minutes{value})
{
}

base::unit::Hours::Hours(std::chrono::microseconds const &value)
	: Hours(base::unit::Minutes{value})
{
}

base::unit::Hours::Hours(std::chrono::nanoseconds const &value)
	: base::unit::Hours(base::unit::Nanoseconds{value})
{
}

/* #endregion */

base::Fraction &base::unit::Hours::Value()
{
	return _value;
}

std::string base::unit::Hours::UnitString() const
{
	return "h";
}

/* #region 强制转换运算符 */

base::unit::Hours::operator std::chrono::days() const
{
	return std::chrono::days{base::unit::Minutes{*this}};
}

base::unit::Hours::operator std::chrono::hours() const
{
	return std::chrono::hours{base::unit::Minutes{*this}};
}

base::unit::Hours::operator std::chrono::minutes() const
{
	return std::chrono::minutes{base::unit::Minutes{*this}};
}

base::unit::Hours::operator std::chrono::seconds() const
{
	return std::chrono::seconds{base::unit::Minutes{*this}};
}

base::unit::Hours::operator std::chrono::milliseconds() const
{
	return std::chrono::milliseconds{base::unit::Minutes{*this}};
}

base::unit::Hours::operator std::chrono::microseconds() const
{
	return std::chrono::microseconds{base::unit::Minutes{*this}};
}

base::unit::Hours::operator std::chrono::nanoseconds() const
{
	return std::chrono::nanoseconds{base::unit::Minutes{*this}};
}

/* #endregion */

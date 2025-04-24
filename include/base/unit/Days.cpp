#include "Days.h"
#include "base/unit/Hours.h"
#include "base/unit/Nanoseconds.h"

/* #region 构造函数 */

base::Days::Days(base::Fraction const &value)
{
	_value = value;
}

base::Days::Days(base::Hours const &value)
{
	_value = static_cast<base::Fraction>(value) / 24;
}

base::Days::Days(base::Minutes const &value)
	: Days(base::Hours{value})
{
}

base::Days::Days(base::Seconds const &value)
	: Days(base::Hours{value})
{
}

base::Days::Days(base::Nanoseconds const &value)
	: Days(base::Hours{value})
{
}

base::Days::Days(base::Hz const &value)
	: Days(base::Hours{value})
{
}

base::Days::Days(base::MHz const &value)
	: Days(base::Hours{value})
{
}

base::Days::Days(std::chrono::seconds const &value)
	: Days(base::Hours{value})
{
}

base::Days::Days(std::chrono::milliseconds const &value)
	: Days(base::Hours{value})
{
}

base::Days::Days(std::chrono::microseconds const &value)
	: Days(base::Hours{value})
{
}

base::Days::Days(std::chrono::nanoseconds const &value)
	: Days(base::Nanoseconds{value})
{
}

/* #endregion */

base::Fraction &base::Days::Value()
{
	return _value;
}

std::string base::Days::UnitString() const
{
	return "d";
}

/* #region 强制转换运算符 */

base::Days::operator std::chrono::days() const
{
	return std::chrono::days{base::Hours{*this}};
}

base::Days::operator std::chrono::hours() const
{
	return std::chrono::hours{base::Hours{*this}};
}

base::Days::operator std::chrono::minutes() const
{
	return std::chrono::minutes{base::Hours{*this}};
}

base::Days::operator std::chrono::seconds() const
{
	return std::chrono::seconds{base::Hours{*this}};
}

base::Days::operator std::chrono::milliseconds() const
{
	return std::chrono::milliseconds{base::Hours{*this}};
}

base::Days::operator std::chrono::microseconds() const
{
	return std::chrono::microseconds{base::Hours{*this}};
}

base::Days::operator std::chrono::nanoseconds() const
{
	return std::chrono::nanoseconds{base::Hours{*this}};
}

/* #endregion */

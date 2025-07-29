#include "base/unit/Hz.h"
#include "base/unit/MHz.h"
#include "base/unit/Seconds.h"
#include "Nanosecond.h"
#include <chrono>


/* #region 构造函数 */

base::unit::Nanosecond::Nanosecond(base::Fraction const &value)
{
	_value = value;
}

base::unit::Nanosecond::Nanosecond(base::unit::Hour const &value)
	: Nanosecond{base::unit::Seconds{value}}
{
}

base::unit::Nanosecond::Nanosecond(base::unit::Minute const &value)
	: Nanosecond{base::unit::Seconds{value}}
{
}

base::unit::Nanosecond::Nanosecond(base::unit::Seconds const &value)
{
	_value = static_cast<base::Fraction>(value) * 1000 * 1000 * 1000;
}

base::unit::Nanosecond::Nanosecond(base::unit::Hz const &value)
	: Nanosecond{base::unit::Seconds{value}}
{
}

base::unit::Nanosecond::Nanosecond(base::unit::MHz const &value)
	: Nanosecond(base::unit::Seconds{value})
{
}

base::unit::Nanosecond::Nanosecond(std::chrono::seconds const &value)
	: Nanosecond(base::unit::Seconds{value})
{
}

base::unit::Nanosecond::Nanosecond(std::chrono::milliseconds const &value)
	: Nanosecond(base::unit::Seconds{value})
{
}

base::unit::Nanosecond::Nanosecond(std::chrono::microseconds const &value)
	: Nanosecond(base::unit::Seconds{value})
{
}

base::unit::Nanosecond::Nanosecond(std::chrono::nanoseconds const &value)
	: Nanosecond(base::unit::Seconds{value})
{
}

/* #endregion */

base::Fraction &base::unit::Nanosecond::Value()
{
	return _value;
}

std::string base::unit::Nanosecond::UnitString() const
{
	return "ns";
}

/* #region 强制转换运算符 */

base::unit::Nanosecond::operator std::chrono::days() const
{
	return std::chrono::days{base::unit::Seconds{*this}};
}

base::unit::Nanosecond::operator std::chrono::hours() const
{
	return std::chrono::hours{base::unit::Seconds{*this}};
}

base::unit::Nanosecond::operator std::chrono::minutes() const
{
	return std::chrono::minutes{base::unit::Seconds{*this}};
}

base::unit::Nanosecond::operator std::chrono::seconds() const
{
	return std::chrono::seconds{base::unit::Seconds{*this}};
}

base::unit::Nanosecond::operator std::chrono::milliseconds() const
{
	return std::chrono::milliseconds{base::unit::Seconds{*this}};
}

base::unit::Nanosecond::operator std::chrono::microseconds() const
{
	return std::chrono::microseconds{base::unit::Seconds{*this}};
}

base::unit::Nanosecond::operator std::chrono::nanoseconds() const
{
	return std::chrono::nanoseconds{base::unit::Seconds{*this}};
}

/* #endregion */

#include "Nanosecond.h"
#include "base/unit/Hz.h"
#include "base/unit/MHz.h"
#include "base/unit/Minute.h"
#include "base/unit/Second.h"
#include <chrono>

/* #region 构造函数 */

base::unit::Nanosecond::Nanosecond(base::Fraction const &value)
{
	_value = value;
}

base::unit::Nanosecond::Nanosecond(base::unit::Hour const &value)
	: Nanosecond{base::unit::Second{value}}
{
}

base::unit::Nanosecond::Nanosecond(base::unit::Minute const &value)
	: Nanosecond{base::unit::Second{value}}
{
}

base::unit::Nanosecond::Nanosecond(base::unit::Second const &value)
{
	_value = static_cast<base::Fraction>(value) * 1000 * 1000 * 1000;
}

base::unit::Nanosecond::Nanosecond(base::unit::Hz const &value)
	: Nanosecond{base::unit::Second{value}}
{
}

base::unit::Nanosecond::Nanosecond(base::unit::MHz const &value)
	: Nanosecond(base::unit::Second{value})
{
}

base::unit::Nanosecond::Nanosecond(std::chrono::seconds const &value)
	: Nanosecond(base::unit::Second{value})
{
}

base::unit::Nanosecond::Nanosecond(std::chrono::milliseconds const &value)
	: Nanosecond(base::unit::Second{value})
{
}

base::unit::Nanosecond::Nanosecond(std::chrono::microseconds const &value)
	: Nanosecond(base::unit::Second{value})
{
}

base::unit::Nanosecond::Nanosecond(std::chrono::nanoseconds const &value)
	: Nanosecond(base::unit::Second{value})
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
	return std::chrono::days{base::unit::Second{*this}};
}

base::unit::Nanosecond::operator std::chrono::hours() const
{
	return std::chrono::hours{base::unit::Second{*this}};
}

base::unit::Nanosecond::operator std::chrono::minutes() const
{
	return std::chrono::minutes{base::unit::Second{*this}};
}

base::unit::Nanosecond::operator std::chrono::seconds() const
{
	return std::chrono::seconds{base::unit::Second{*this}};
}

base::unit::Nanosecond::operator std::chrono::milliseconds() const
{
	return std::chrono::milliseconds{base::unit::Second{*this}};
}

base::unit::Nanosecond::operator std::chrono::microseconds() const
{
	return std::chrono::microseconds{base::unit::Second{*this}};
}

base::unit::Nanosecond::operator std::chrono::nanoseconds() const
{
	return std::chrono::nanoseconds{base::unit::Second{*this}};
}

/* #endregion */

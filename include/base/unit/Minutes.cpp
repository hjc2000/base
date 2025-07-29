#include "Minutes.h"
#include "base/unit/Hour.h"
#include "base/unit/Seconds.h"
#include "Nanoseconds.h"

/* #region 构造函数 */

base::unit::Minutes::Minutes(base::Fraction const &value)
{
	_value = value;
}

base::unit::Minutes::Minutes(base::unit::Hour const &value)
{
	_value = static_cast<base::Fraction>(value) * 60;
}

base::unit::Minutes::Minutes(base::unit::Seconds const &value)
{
	_value = static_cast<base::Fraction>(value) / 60;
}

base::unit::Minutes::Minutes(base::unit::Nanoseconds const &value)
	: Minutes(base::unit::Seconds{value})
{
}

base::unit::Minutes::Minutes(base::unit::Hz const &value)
	: Minutes(base::unit::Seconds{value})
{
}

base::unit::Minutes::Minutes(base::unit::MHz const &value)
	: Minutes(base::unit::Seconds{value})
{
}

base::unit::Minutes::Minutes(std::chrono::seconds const &value)
	: Minutes(base::unit::Seconds{value})
{
}

base::unit::Minutes::Minutes(std::chrono::milliseconds const &value)
	: Minutes(base::unit::Seconds{value})
{
}

base::unit::Minutes::Minutes(std::chrono::microseconds const &value)
	: Minutes(base::unit::Seconds{value})
{
}

base::unit::Minutes::Minutes(std::chrono::nanoseconds const &value)
	: base::unit::Minutes(base::unit::Nanoseconds{value})
{
}

/* #endregion */

base::Fraction &base::unit::Minutes::Value()
{
	return _value;
}

std::string base::unit::Minutes::UnitString() const
{
	return "m";
}

/* #region 强制转换运算符 */

base::unit::Minutes::operator std::chrono::days() const
{
	return std::chrono::days{base::unit::Seconds{*this}};
}

base::unit::Minutes::operator std::chrono::hours() const
{
	return std::chrono::hours{base::unit::Seconds{*this}};
}

base::unit::Minutes::operator std::chrono::minutes() const
{
	return std::chrono::minutes{base::unit::Seconds{*this}};
}

base::unit::Minutes::operator std::chrono::seconds() const
{
	return std::chrono::seconds{base::unit::Seconds{*this}};
}

base::unit::Minutes::operator std::chrono::milliseconds() const
{
	return std::chrono::milliseconds{base::unit::Seconds{*this}};
}

base::unit::Minutes::operator std::chrono::microseconds() const
{
	return std::chrono::microseconds{base::unit::Seconds{*this}};
}

base::unit::Minutes::operator std::chrono::nanoseconds() const
{
	return std::chrono::nanoseconds{base::unit::Seconds{*this}};
}

/* #endregion */

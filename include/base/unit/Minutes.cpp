#include "Minutes.h"
#include "base/unit/Hours.h"
#include "base/unit/Seconds.h"
#include "Nanoseconds.h"

/* #region 构造函数 */

base::Minutes::Minutes(base::Fraction const &value)
{
	_value = value;
}

base::Minutes::Minutes(int64_t value)
{
	_value = value;
}

base::Minutes::Minutes(base::Hours const &value)
{
	_value = static_cast<base::Fraction>(value) * 60;
}

base::Minutes::Minutes(base::Seconds const &value)
{
	_value = static_cast<base::Fraction>(value) / 60;
}

base::Minutes::Minutes(base::Nanoseconds const &value)
	: Minutes(base::Seconds{value})
{
}

base::Minutes::Minutes(base::Hz const &value)
	: Minutes(base::Seconds{value})
{
}

base::Minutes::Minutes(base::MHz const &value)
	: Minutes(base::Seconds{value})
{
}

base::Minutes::Minutes(std::chrono::seconds const &value)
	: Minutes(base::Seconds{value})
{
}

base::Minutes::Minutes(std::chrono::milliseconds const &value)
	: Minutes(base::Seconds{value})
{
}

base::Minutes::Minutes(std::chrono::microseconds const &value)
	: Minutes(base::Seconds{value})
{
}

base::Minutes::Minutes(std::chrono::nanoseconds const &value)
	: base::Minutes(base::Nanoseconds{value})
{
}

/* #endregion */

base::Fraction &base::Minutes::Value()
{
	return _value;
}

std::string base::Minutes::UnitString() const
{
	return "m";
}

/* #region 强制转换运算符 */

base::Minutes::operator std::chrono::seconds() const
{
	return std::chrono::seconds{base::Seconds{*this}};
}

base::Minutes::operator std::chrono::milliseconds() const
{
	return std::chrono::seconds{base::Seconds{*this}};
}

base::Minutes::operator std::chrono::microseconds() const
{
	return std::chrono::seconds{base::Seconds{*this}};
}

/* #endregion */

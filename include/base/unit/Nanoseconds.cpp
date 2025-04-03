#include "Nanoseconds.h"
#include "base/unit/Hz.h"
#include "base/unit/MHz.h"
#include "base/unit/Seconds.h"
#include <chrono>

/* #region 构造函数 */

base::Nanoseconds::Nanoseconds(base::Fraction const &value)
{
	_value = value;
}

base::Nanoseconds::Nanoseconds(int64_t value)
{
	_value = value;
}

base::Nanoseconds::Nanoseconds(base::Hours const &value)
	: Nanoseconds{base::Seconds{value}}
{
}

base::Nanoseconds::Nanoseconds(base::Minutes const &value)
	: Nanoseconds{base::Seconds{value}}
{
}

base::Nanoseconds::Nanoseconds(base::Seconds const &value)
{
	_value = static_cast<base::Fraction>(value) * 1000 * 1000 * 1000;
}

base::Nanoseconds::Nanoseconds(base::Hz const &value)
	: Nanoseconds{base::Seconds{value}}
{
}

base::Nanoseconds::Nanoseconds(base::MHz const &value)
	: Nanoseconds(base::Seconds{value})
{
}

base::Nanoseconds::Nanoseconds(std::chrono::seconds const &value)
	: Nanoseconds(base::Seconds{value})
{
}

base::Nanoseconds::Nanoseconds(std::chrono::milliseconds const &value)
	: Nanoseconds(base::Seconds{value})
{
}

base::Nanoseconds::Nanoseconds(std::chrono::microseconds const &value)
	: Nanoseconds(base::Seconds{value})
{
}

base::Nanoseconds::Nanoseconds(std::chrono::nanoseconds const &value)
	: Nanoseconds(base::Seconds{value})
{
}

/* #endregion */

base::Fraction &base::Nanoseconds::Value()
{
	return _value;
}

std::string base::Nanoseconds::UnitString() const
{
	return "ns";
}

/* #region 强制转换运算符 */

base::Nanoseconds::operator std::chrono::days() const
{
	return std::chrono::days{base::Seconds{*this}};
}

base::Nanoseconds::operator std::chrono::hours() const
{
	return std::chrono::hours{base::Seconds{*this}};
}

base::Nanoseconds::operator std::chrono::minutes() const
{
	return std::chrono::minutes{base::Seconds{*this}};
}

base::Nanoseconds::operator std::chrono::seconds() const
{
	return std::chrono::seconds{base::Seconds{*this}};
}

base::Nanoseconds::operator std::chrono::milliseconds() const
{
	return std::chrono::milliseconds{base::Seconds{*this}};
}

base::Nanoseconds::operator std::chrono::microseconds() const
{
	return std::chrono::microseconds{base::Seconds{*this}};
}

base::Nanoseconds::operator std::chrono::nanoseconds() const
{
	return std::chrono::nanoseconds{base::Seconds{*this}};
}

/* #endregion */

#include "Seconds.h"
#include "base/unit/Hours.h"
#include "base/unit/Hz.h"
#include "base/unit/Minutes.h"
#include "base/unit/Nanoseconds.h"
#include <chrono>

/* #region 构造函数 */

base::Seconds::Seconds(base::Fraction const &value)
{
	_value = value;
}

base::Seconds::Seconds(base::Hours const &value)
{
	_value = static_cast<base::Fraction>(value) * 60 * 60;
}

base::Seconds::Seconds(base::Minutes const &value)
{
	_value = static_cast<base::Fraction>(value) * 60;
}

base::Seconds::Seconds(base::Nanoseconds const &value)
{
	_value = static_cast<base::Fraction>(value) / 1000 / 1000 / 1000;
}

base::Seconds::Seconds(base::Hz const &value)
{
	_value = static_cast<base::Fraction>(value).Reciprocal();
}

base::Seconds::Seconds(base::MHz const &value)
	: Seconds(base::Hz{value})
{
}

base::Seconds::Seconds(std::chrono::seconds const &value)
{
	_value = base::Fraction{value.count()};
}

base::Seconds::Seconds(std::chrono::milliseconds const &value)
{
	_value = base::Fraction{value.count()} / 1000;
}

base::Seconds::Seconds(std::chrono::microseconds const &value)
{
	_value = base::Fraction{value.count()} / 1000 / 1000;
}

base::Seconds::Seconds(std::chrono::nanoseconds const &value)
{
	_value = base::Fraction{value.count()} / 1000 / 1000 / 1000;
}

/* #endregion */

base::Fraction &base::Seconds::Value()
{
	return _value;
}

std::string base::Seconds::UnitString() const
{
	return "s";
}

/* #region 强制转换运算符 */

base::Seconds::operator std::chrono::days() const
{
	return std::chrono::days{static_cast<int64_t>(_value / 60 / 60 / 24)};
}

base::Seconds::operator std::chrono::hours() const
{
	return std::chrono::hours{static_cast<int64_t>(_value / 60 / 60)};
}

base::Seconds::operator std::chrono::minutes() const
{
	return std::chrono::minutes{static_cast<int64_t>(_value / 60)};
}

base::Seconds::operator std::chrono::seconds() const
{
	return std::chrono::seconds{static_cast<int64_t>(_value)};
}

base::Seconds::operator std::chrono::milliseconds() const
{
	return std::chrono::milliseconds{static_cast<int64_t>(_value * 1000)};
}

base::Seconds::operator std::chrono::microseconds() const
{
	return std::chrono::microseconds{static_cast<int64_t>(_value * 1000 * 1000)};
}

base::Seconds::operator std::chrono::nanoseconds() const
{
	return std::chrono::nanoseconds{static_cast<int64_t>(_value * 1000 * 1000 * 1000)};
}

/* #endregion */

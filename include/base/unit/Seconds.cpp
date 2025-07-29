#include "Seconds.h"
#include "base/unit/Hour.h"
#include "base/unit/Hz.h"
#include "base/unit/Minute.h"
#include "base/unit/Nanosecond.h"
#include <chrono>

/* #region 构造函数 */

base::unit::Seconds::Seconds(base::Fraction const &value)
{
	_value = value;
}

base::unit::Seconds::Seconds(base::unit::Hour const &value)
{
	_value = static_cast<base::Fraction>(value) * 60 * 60;
}

base::unit::Seconds::Seconds(base::unit::Minute const &value)
{
	_value = static_cast<base::Fraction>(value) * 60;
}

base::unit::Seconds::Seconds(base::unit::Nanosecond const &value)
{
	_value = static_cast<base::Fraction>(value) / 1000 / 1000 / 1000;
}

base::unit::Seconds::Seconds(base::unit::Hz const &value)
{
	_value = static_cast<base::Fraction>(value).Reciprocal();
}

base::unit::Seconds::Seconds(base::unit::MHz const &value)
	: Seconds(base::unit::Hz{value})
{
}

base::unit::Seconds::Seconds(std::chrono::seconds const &value)
{
	_value = base::Fraction{value.count()};
}

base::unit::Seconds::Seconds(std::chrono::milliseconds const &value)
{
	_value = base::Fraction{value.count()} / 1000;
}

base::unit::Seconds::Seconds(std::chrono::microseconds const &value)
{
	_value = base::Fraction{value.count()} / 1000 / 1000;
}

base::unit::Seconds::Seconds(std::chrono::nanoseconds const &value)
{
	_value = base::Fraction{value.count()} / 1000 / 1000 / 1000;
}

/* #endregion */

base::Fraction &base::unit::Seconds::Value()
{
	return _value;
}

std::string base::unit::Seconds::UnitString() const
{
	return "s";
}

/* #region 强制转换运算符 */

base::unit::Seconds::operator std::chrono::days() const
{
	return std::chrono::days{static_cast<int64_t>(_value / 60 / 60 / 24)};
}

base::unit::Seconds::operator std::chrono::hours() const
{
	return std::chrono::hours{static_cast<int64_t>(_value / 60 / 60)};
}

base::unit::Seconds::operator std::chrono::minutes() const
{
	return std::chrono::minutes{static_cast<int64_t>(_value / 60)};
}

base::unit::Seconds::operator std::chrono::seconds() const
{
	return std::chrono::seconds{static_cast<int64_t>(_value)};
}

base::unit::Seconds::operator std::chrono::milliseconds() const
{
	return std::chrono::milliseconds{static_cast<int64_t>(_value * 1000)};
}

base::unit::Seconds::operator std::chrono::microseconds() const
{
	return std::chrono::microseconds{static_cast<int64_t>(_value * 1000 * 1000)};
}

base::unit::Seconds::operator std::chrono::nanoseconds() const
{
	return std::chrono::nanoseconds{static_cast<int64_t>(_value * 1000 * 1000 * 1000)};
}

/* #endregion */

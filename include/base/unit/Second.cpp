#include "Second.h"
#include "base/unit/Hour.h"
#include "base/unit/Hz.h"
#include "base/unit/Nanosecond.h"
#include <chrono>

/* #region 构造函数 */

base::unit::Second::Second(base::Fraction const &value)
{
	_value = value;
}

base::unit::Second::Second(base::unit::Hour const &value)
{
	_value = static_cast<base::Fraction>(value) * 60 * 60;
}

base::unit::Second::Second(base::unit::Hz const &value)
{
	_value = static_cast<base::Fraction>(value).Reciprocal();
}

base::unit::Second::Second(base::unit::MHz const &value)
	: Second(base::unit::Hz{value})
{
}

base::unit::Second::Second(std::chrono::seconds const &value)
{
	_value = base::Fraction{value.count()};
}

base::unit::Second::Second(std::chrono::milliseconds const &value)
{
	_value = base::Fraction{value.count()} / 1000;
}

base::unit::Second::Second(std::chrono::microseconds const &value)
{
	_value = base::Fraction{value.count()} / 1000 / 1000;
}

base::unit::Second::Second(std::chrono::nanoseconds const &value)
{
	_value = base::Fraction{value.count()} / 1000 / 1000 / 1000;
}

/* #endregion */

base::Fraction &base::unit::Second::Value()
{
	return _value;
}

std::string base::unit::Second::UnitString() const
{
	return "s";
}

/* #region 强制转换运算符 */

base::unit::Second::operator std::chrono::days() const
{
	return std::chrono::days{static_cast<int64_t>(_value / 60 / 60 / 24)};
}

base::unit::Second::operator std::chrono::hours() const
{
	return std::chrono::hours{static_cast<int64_t>(_value / 60 / 60)};
}

base::unit::Second::operator std::chrono::minutes() const
{
	return std::chrono::minutes{static_cast<int64_t>(_value / 60)};
}

base::unit::Second::operator std::chrono::seconds() const
{
	return std::chrono::seconds{static_cast<int64_t>(_value)};
}

base::unit::Second::operator std::chrono::milliseconds() const
{
	return std::chrono::milliseconds{static_cast<int64_t>(_value * 1000)};
}

base::unit::Second::operator std::chrono::microseconds() const
{
	return std::chrono::microseconds{static_cast<int64_t>(_value * 1000 * 1000)};
}

base::unit::Second::operator std::chrono::nanoseconds() const
{
	return std::chrono::nanoseconds{static_cast<int64_t>(_value * 1000 * 1000 * 1000)};
}

/* #endregion */

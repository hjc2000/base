#include "Second.h"
#include "base/unit/Hour.h"
#include "base/unit/Hz.h"
#include "base/unit/Nanosecond.h"

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

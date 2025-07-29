#include "MHz.h"
#include "base/unit/Hz.h"
#include "base/unit/Seconds.h"

/* #region 构造函数 */

base::unit::MHz::MHz(base::Fraction const &value)
{
	_value = value;
}

base::unit::MHz::MHz(base::unit::Hz const &value)
{
	_value = static_cast<base::Fraction>(value) / 1000 / 1000;
}

base::unit::MHz::MHz(base::unit::Seconds const &value)
	: MHz(base::unit::Hz{value})
{
}

base::unit::MHz::MHz(base::unit::Nanosecond const &value)
	: MHz(base::unit::Seconds{value})
{
}

/* #endregion */

base::Fraction &base::unit::MHz::Value()
{
	return _value;
}

std::string base::unit::MHz::UnitString() const
{
	return "MHz";
}

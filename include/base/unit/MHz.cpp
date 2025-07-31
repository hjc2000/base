#include "MHz.h"
#include "base/unit/Nanosecond.h"

/* #region 构造函数 */

base::unit::MHz::MHz(base::unit::Hz const &value)
{
	_value = static_cast<base::Fraction>(value) / 1000 / 1000;
}

base::unit::MHz::MHz(base::unit::Nanosecond const &value)
	: MHz(base::unit::Second{value})
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

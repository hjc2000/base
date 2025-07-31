#include "Hz.h"
#include "base/unit/MHz.h"
#include "base/unit/Nanosecond.h"
#include "base/unit/Second.h"

/* #region 构造函数 */

base::unit::Hz::Hz(base::unit::MHz const &value)
{
	_value = static_cast<base::Fraction>(value) * 1000 * 1000;
}

base::unit::Hz::Hz(base::unit::Nanosecond const &value)
	: Hz(base::unit::Second{value})
{
}

/* #endregion */

base::Fraction &base::unit::Hz::Value()
{
	return _value;
}

std::string base::unit::Hz::UnitString() const
{
	return "Hz";
}

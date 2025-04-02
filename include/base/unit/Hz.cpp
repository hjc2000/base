#include "Hz.h"
#include "base/unit/MHz.h"
#include "base/unit/Seconds.h"

/* #region 构造函数 */

base::Hz::Hz(base::Fraction const &value)
{
	_value = value;
}

base::Hz::Hz(base::MHz const &value)
{
	_value = static_cast<base::Fraction>(value) * 1000 * 1000;
}

base::Hz::Hz(int64_t value)
{
	_value = value;
}

base::Hz::Hz(base::Seconds const &value)
{
	_value = static_cast<base::Fraction>(value).Reciprocal();
}

base::Hz::Hz(base::Nanoseconds const &value)
	: Hz(base::Seconds{value})
{
}

/* #endregion */

base::Fraction &base::Hz::Value()
{
	return _value;
}

std::string base::Hz::UnitString() const
{
	return "Hz";
}

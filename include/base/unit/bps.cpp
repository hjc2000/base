#include "bps.h"
#include <base/unit/Mbps.h>

/* #region 构造函数 */

base::bps::bps(base::Fraction const &o)
{
	_value = o;
}

base::bps::bps(Mbps const &o)
{
	_value = static_cast<base::Fraction>(o) * 1000 * 1000;
}

/* #endregion */

base::Fraction &base::bps::Value()
{
	return _value;
}

std::string base::bps::UnitString() const
{
	return "bps";
}

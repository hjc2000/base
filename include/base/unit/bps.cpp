#include "bps.h"
#include "base/unit/Mbps.h"

/* #region 构造函数 */

base::unit::bps::bps(base::Fraction const &o)
{
	_value = o;
}

base::unit::bps::bps(base::unit::Mbps const &o)
{
	_value = static_cast<base::Fraction>(o) * 1000 * 1000;
}

/* #endregion */

base::Fraction &base::unit::bps::Value()
{
	return _value;
}

std::string base::unit::bps::UnitString() const
{
	return "bps";
}

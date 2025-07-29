#include "Nm.h"

/* #region 构造函数 */

base::unit::Nm::Nm(base::Fraction const &value)
{
	_value = value;
}

/* #endregion */

base::Fraction &base::unit::Nm::Value()
{
	return _value;
}

std::string base::unit::Nm::UnitString() const
{
	return "N·m";
}

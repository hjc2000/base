#include "Nm.h"

/* #region 构造函数 */

base::Nm::Nm(int64_t value)
{
	_value = value;
}

base::Nm::Nm(base::Fraction const &value)
{
	_value = value;
}

/* #endregion */

base::Fraction &base::Nm::Value()
{
	return _value;
}

std::string base::Nm::UnitString() const
{
	return "N·m";
}

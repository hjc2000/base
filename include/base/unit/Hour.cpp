#include "Hour.h"
#include "base/unit/Day.h"
#include "base/unit/Minute.h"
#include "Nanosecond.h"

/* #region 构造函数 */

base::unit::Hour::Hour(base::unit::Day const &value)
{
	_value = static_cast<base::Fraction>(value) * 24;
}

/* #endregion */

base::Fraction &base::unit::Hour::Value()
{
	return _value;
}

std::string base::unit::Hour::UnitString() const
{
	return "h";
}

/* #region 强制转换运算符 */

base::unit::Hour::operator std::chrono::days() const
{
	return std::chrono::days{base::unit::Minute{*this}};
}

base::unit::Hour::operator std::chrono::hours() const
{
	return std::chrono::hours{base::unit::Minute{*this}};
}

base::unit::Hour::operator std::chrono::minutes() const
{
	return std::chrono::minutes{base::unit::Minute{*this}};
}

base::unit::Hour::operator std::chrono::seconds() const
{
	return std::chrono::seconds{base::unit::Minute{*this}};
}

base::unit::Hour::operator std::chrono::milliseconds() const
{
	return std::chrono::milliseconds{base::unit::Minute{*this}};
}

base::unit::Hour::operator std::chrono::microseconds() const
{
	return std::chrono::microseconds{base::unit::Minute{*this}};
}

base::unit::Hour::operator std::chrono::nanoseconds() const
{
	return std::chrono::nanoseconds{base::unit::Minute{*this}};
}

/* #endregion */

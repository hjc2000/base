#include "Day.h"
#include "base/unit/Hour.h"
#include "base/unit/Hz.h"
#include "base/unit/MHz.h"
#include "base/unit/Minute.h"
#include "base/unit/Nanosecond.h"

/* #region 构造函数 */

base::unit::Day::Day(base::Fraction const &value)
{
	_value = value;
}

base::unit::Day::Day(base::unit::Hour const &value)
{
	_value = static_cast<base::Fraction>(value) / 24;
}

base::unit::Day::Day(base::unit::Minute const &value)
	: Day(base::unit::Hour{value})
{
}

base::unit::Day::Day(base::unit::Second const &value)
	: Day(base::unit::Hour{value})
{
}

base::unit::Day::Day(base::unit::Nanosecond const &value)
	: Day(base::unit::Hour{value})
{
}

base::unit::Day::Day(base::unit::Hz const &value)
	: Day(base::unit::Hour{value})
{
}

base::unit::Day::Day(base::unit::MHz const &value)
	: Day(base::unit::Hour{value})
{
}

base::unit::Day::Day(std::chrono::seconds const &value)
	: Day(base::unit::Hour{value})
{
}

base::unit::Day::Day(std::chrono::milliseconds const &value)
	: Day(base::unit::Hour{value})
{
}

base::unit::Day::Day(std::chrono::microseconds const &value)
	: Day(base::unit::Hour{value})
{
}

base::unit::Day::Day(std::chrono::nanoseconds const &value)
	: Day(base::unit::Nanosecond{value})
{
}

/* #endregion */

base::Fraction &base::unit::Day::Value()
{
	return _value;
}

std::string base::unit::Day::UnitString() const
{
	return "d";
}

/* #region 强制转换运算符 */

base::unit::Day::operator std::chrono::days() const
{
	return std::chrono::days{base::unit::Hour{*this}};
}

base::unit::Day::operator std::chrono::hours() const
{
	return std::chrono::hours{base::unit::Hour{*this}};
}

base::unit::Day::operator std::chrono::minutes() const
{
	return std::chrono::minutes{base::unit::Hour{*this}};
}

base::unit::Day::operator std::chrono::seconds() const
{
	return std::chrono::seconds{base::unit::Hour{*this}};
}

base::unit::Day::operator std::chrono::milliseconds() const
{
	return std::chrono::milliseconds{base::unit::Hour{*this}};
}

base::unit::Day::operator std::chrono::microseconds() const
{
	return std::chrono::microseconds{base::unit::Hour{*this}};
}

base::unit::Day::operator std::chrono::nanoseconds() const
{
	return std::chrono::nanoseconds{base::unit::Hour{*this}};
}

/* #endregion */

#include "Minute.h"
#include "base/unit/Hour.h"
#include "base/unit/Second.h"
#include "Nanosecond.h"

/* #region 构造函数 */

base::unit::Minute::Minute(base::Fraction const &value)
{
	_value = value;
}

base::unit::Minute::Minute(base::unit::Hour const &value)
{
	_value = static_cast<base::Fraction>(value) * 60;
}

base::unit::Minute::Minute(base::unit::Second const &value)
{
	_value = static_cast<base::Fraction>(value) / 60;
}

base::unit::Minute::Minute(base::unit::Nanosecond const &value)
	: Minute(base::unit::Second{value})
{
}

base::unit::Minute::Minute(base::unit::Hz const &value)
	: Minute(base::unit::Second{value})
{
}

base::unit::Minute::Minute(base::unit::MHz const &value)
	: Minute(base::unit::Second{value})
{
}

base::unit::Minute::Minute(std::chrono::seconds const &value)
	: Minute(base::unit::Second{value})
{
}

base::unit::Minute::Minute(std::chrono::milliseconds const &value)
	: Minute(base::unit::Second{value})
{
}

base::unit::Minute::Minute(std::chrono::microseconds const &value)
	: Minute(base::unit::Second{value})
{
}

base::unit::Minute::Minute(std::chrono::nanoseconds const &value)
	: base::unit::Minute(base::unit::Nanosecond{value})
{
}

/* #endregion */

/* #region 强制转换运算符 */

base::unit::Minute::operator std::chrono::days() const
{
	return std::chrono::days{base::unit::Second{*this}};
}

base::unit::Minute::operator std::chrono::hours() const
{
	return std::chrono::hours{base::unit::Second{*this}};
}

base::unit::Minute::operator std::chrono::minutes() const
{
	return std::chrono::minutes{base::unit::Second{*this}};
}

base::unit::Minute::operator std::chrono::seconds() const
{
	return std::chrono::seconds{base::unit::Second{*this}};
}

base::unit::Minute::operator std::chrono::milliseconds() const
{
	return std::chrono::milliseconds{base::unit::Second{*this}};
}

base::unit::Minute::operator std::chrono::microseconds() const
{
	return std::chrono::microseconds{base::unit::Second{*this}};
}

base::unit::Minute::operator std::chrono::nanoseconds() const
{
	return std::chrono::nanoseconds{base::unit::Second{*this}};
}

/* #endregion */

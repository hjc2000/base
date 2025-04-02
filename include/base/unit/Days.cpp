#include "Days.h"
#include "base/unit/Hours.h"
#include "base/unit/Nanoseconds.h"

/* #region 构造函数 */

base::Days::Days(base::Fraction const &value)
{
	_value = value;
}

base::Days::Days(int64_t value)
{
	_value = value;
}

base::Days::Days(base::Hours const &value)
{
	_value = static_cast<base::Fraction>(value) / 24;
}

base::Days::Days(base::Minutes const &value)
	: Days(base::Hours{value})
{
}

base::Days::Days(base::Seconds const &value)
	: Days(base::Hours{value})
{
}

base::Days::Days(base::Nanoseconds const &value)
	: Days(base::Hours{value})
{
}

base::Days::Days(base::Hz const &value)
	: Days(base::Hours{value})
{
}

base::Days::Days(base::MHz const &value)
	: Days(base::Hours{value})
{
}

base::Days::Days(std::chrono::seconds const &value)
	: Days(base::Hours{value})
{
}

base::Days::Days(std::chrono::milliseconds const &value)
	: Days(base::Hours{value})
{
}

base::Days::Days(std::chrono::microseconds const &value)
	: Days(base::Hours{value})
{
}

base::Days::Days(std::chrono::nanoseconds const &value)
	: Days(base::Nanoseconds{value})
{
}

/* #endregion */

/* #region 强制转换运算符 */

base::Days::operator std::chrono::seconds() const
{
	return std::chrono::seconds{base::Hours{*this}};
}

base::Days::operator std::chrono::milliseconds() const
{
	return std::chrono::seconds{base::Hours{*this}};
}

base::Days::operator std::chrono::microseconds() const
{
	return std::chrono::seconds{base::Hours{*this}};
}

/* #endregion */

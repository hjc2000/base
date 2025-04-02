#include "Nanoseconds.h"
#include "base/unit/Hz.h"
#include "base/unit/MHz.h"
#include "base/unit/Seconds.h"
#include <chrono>

/* #region 构造函数 */

base::Nanoseconds::Nanoseconds(base::Fraction const &value)
{
	_value = value;
}

base::Nanoseconds::Nanoseconds(int64_t value)
{
	_value = value;
}

base::Nanoseconds::Nanoseconds(base::Hours const &value)
	: Nanoseconds{base::Seconds{value}}
{
}

base::Nanoseconds::Nanoseconds(base::Minutes const &value)
	: Nanoseconds{base::Seconds{value}}
{
}

base::Nanoseconds::Nanoseconds(base::Seconds const &value)
{
	_value = static_cast<base::Fraction>(value) * 1000 * 1000 * 1000;
}

base::Nanoseconds::Nanoseconds(base::Hz const &value)
	: Nanoseconds{base::Seconds{value}}
{
}

base::Nanoseconds::Nanoseconds(base::MHz const &value)
	: Nanoseconds(base::Seconds{value})
{
}

base::Nanoseconds::Nanoseconds(std::chrono::seconds const &value)
	: Nanoseconds(base::Seconds{value})
{
}

base::Nanoseconds::Nanoseconds(std::chrono::milliseconds const &value)
	: Nanoseconds(base::Seconds{value})
{
}

base::Nanoseconds::Nanoseconds(std::chrono::microseconds const &value)
	: Nanoseconds(base::Seconds{value})
{
}

base::Nanoseconds::Nanoseconds(std::chrono::nanoseconds const &value)
	: Nanoseconds(base::Seconds{value})
{
}

/* #endregion */

base::Fraction &base::Nanoseconds::Value()
{
	return _value;
}

std::string base::Nanoseconds::UnitString() const
{
	return "ns";
}

/* #region 强制转换运算符 */

base::Nanoseconds::operator std::chrono::seconds() const
{
	std::chrono::nanoseconds ns = static_cast<std::chrono::nanoseconds>(*this);
	return std::chrono::duration_cast<std::chrono::seconds>(ns);
}

base::Nanoseconds::operator std::chrono::milliseconds() const
{
	std::chrono::nanoseconds ns = static_cast<std::chrono::nanoseconds>(*this);
	return std::chrono::duration_cast<std::chrono::milliseconds>(ns);
}

base::Nanoseconds::operator std::chrono::microseconds() const
{
	std::chrono::nanoseconds ns = static_cast<std::chrono::nanoseconds>(*this);
	return std::chrono::duration_cast<std::chrono::microseconds>(ns);
}

base::Nanoseconds::operator std::chrono::nanoseconds() const
{
	return std::chrono::nanoseconds{static_cast<int64_t>(_value)};
}

/* #endregion */

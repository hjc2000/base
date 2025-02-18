#include "Nanoseconds.h"
#include <base/unit/Hz.h>
#include <base/unit/MHz.h>
#include <base/unit/Seconds.h>

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

std::string base::Nanoseconds::UnitString() const
{
	return "ns";
}

#pragma region 强制转换运算符

base::Nanoseconds::operator std::chrono::seconds() const
{
	// 纳秒转换到秒，发生了精度损失。
	std::chrono::milliseconds milliseconds = static_cast<std::chrono::milliseconds>(*this);
	return std::chrono::duration_cast<std::chrono::seconds>(milliseconds);
}

base::Nanoseconds::operator std::chrono::milliseconds() const
{
	// 纳秒转换到毫秒，发生了精度损失。
	std::chrono::microseconds microseconds = static_cast<std::chrono::microseconds>(*this);
	return std::chrono::duration_cast<std::chrono::milliseconds>(microseconds);
}

base::Nanoseconds::operator std::chrono::microseconds() const
{
	// 纳秒转换到微秒，发生了精度损失。
	return std::chrono::microseconds{static_cast<int64_t>(_value / 1000)};
}

#pragma endregion

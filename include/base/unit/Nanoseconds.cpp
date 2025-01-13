#include "Nanoseconds.h"
#include <base/unit/Hz.h>

#pragma region 生命周期

base::Nanoseconds::Nanoseconds(Nanoseconds const &o)
{
	*this = o;
}

base::Nanoseconds::Nanoseconds(base::Fraction const &value)
{
	_value = value;
}

base::Nanoseconds::Nanoseconds(int64_t value)
{
	_value = value;
}

base::Nanoseconds::Nanoseconds(base::Hz const &value)
{
	_value = static_cast<base::Fraction>(value).Reciprocal();
}

base::Nanoseconds::Nanoseconds(std::chrono::seconds const &value)
{
	_value = value.count();
}

base::Nanoseconds::Nanoseconds(std::chrono::milliseconds const &value)
{
	_value = base::Fraction{value.count()} / 1000;
}

base::Nanoseconds::Nanoseconds(std::chrono::microseconds const &value)
{
	_value = base::Fraction{value.count()} / 1000 / 1000;
}

base::Nanoseconds &base::Nanoseconds::operator=(Nanoseconds const &o)
{
	_value = o._value;
	return *this;
}

#pragma endregion

#pragma region 重载强制转换运算符

base::Nanoseconds::operator base::Fraction() const
{
	return _value;
}

base::Nanoseconds::operator std::chrono::seconds() const
{
	return std::chrono::seconds{static_cast<int64_t>(_value / 1000 / 1000 / 1000)};
}

base::Nanoseconds::operator std::chrono::milliseconds() const
{
	return std::chrono::milliseconds{static_cast<int64_t>(_value / 1000 / 1000)};
}

base::Nanoseconds::operator std::chrono::microseconds() const
{
	return std::chrono::microseconds{static_cast<int64_t>(_value / 1000)};
}

base::Nanoseconds::operator int64_t() const
{
	return static_cast<int64_t>(_value);
}

base::Nanoseconds::operator double() const
{
	return static_cast<double>(_value);
}

base::Nanoseconds::operator std::string() const
{
	return static_cast<std::string>(_value);
}

#pragma endregion

#pragma region 重载四则运算符

base::Nanoseconds base::Nanoseconds::operator-() const
{
	return -_value;
}

base::Nanoseconds base::Nanoseconds::operator+(Nanoseconds const &value) const
{
	return _value + static_cast<base::Fraction>(value);
}

base::Nanoseconds base::Nanoseconds::operator-(Nanoseconds const &value) const
{
	return _value - static_cast<base::Fraction>(value);
}

base::Nanoseconds base::Nanoseconds::operator*(Nanoseconds const &value) const
{
	return _value * static_cast<base::Fraction>(value);
}

base::Nanoseconds base::Nanoseconds::operator/(Nanoseconds const &value) const
{
	return _value / static_cast<base::Fraction>(value);
}

base::Nanoseconds &base::Nanoseconds::operator+=(Nanoseconds const &value)
{
	_value += static_cast<base::Fraction>(value);
	return *this;
}

base::Nanoseconds &base::Nanoseconds::operator-=(Nanoseconds const &value)
{
	_value -= static_cast<base::Fraction>(value);
	return *this;
}

base::Nanoseconds &base::Nanoseconds::operator*=(Nanoseconds const &value)
{
	_value *= static_cast<base::Fraction>(value);
	return *this;
}

base::Nanoseconds &base::Nanoseconds::operator/=(Nanoseconds const &value)
{
	_value /= static_cast<base::Fraction>(value);
	return *this;
}

#pragma endregion

#include "Seconds.h"
#include <base/unit/Hz.h>
#include <base/unit/Nanoseconds.h>

#pragma region 生命周期

base::Seconds::Seconds(Seconds const &o)
{
	*this = o;
}

base::Seconds::Seconds(base::Fraction const &value)
{
	_value = value;
}

base::Seconds::Seconds(int64_t value)
{
	_value = value;
}

base::Seconds::Seconds(base::Nanoseconds const &value)
{
	_value = static_cast<base::Fraction>(value) / 1000 / 1000 / 1000;
}

base::Seconds::Seconds(base::Hz const &value)
{
	_value = static_cast<base::Fraction>(value).Reciprocal();
}

base::Seconds::Seconds(std::chrono::seconds const &value)
{
	_value = base::Fraction{value.count()};
}

base::Seconds::Seconds(std::chrono::milliseconds const &value)
{
	_value = base::Fraction{value.count()} / 1000;
}

base::Seconds::Seconds(std::chrono::microseconds const &value)
{
	_value = base::Fraction{value.count()} / 1000 / 1000;
}

base::Seconds &base::Seconds::operator=(Seconds const &o)
{
	_value = o._value;
	return *this;
}

#pragma endregion

#pragma region 重载全局运算符

std::ostream &operator<<(std::ostream &ostream, base::Seconds const &right)
{
	ostream << static_cast<base::Fraction>(right);
	return ostream;
}

base::Seconds operator+(int64_t left, base::Seconds const &right)
{
	return left + static_cast<base::Fraction>(right);
}

base::Seconds operator-(int64_t left, base::Seconds const &right)
{
	return left - static_cast<base::Fraction>(right);
}

base::Seconds operator*(int64_t left, base::Seconds const &right)
{
	return left * static_cast<base::Fraction>(right);
}

base::Seconds operator/(int64_t left, base::Seconds const &right)
{
	return left / static_cast<base::Fraction>(right);
}

#pragma endregion

int64_t std::floor(base::Seconds const &value)
{
	return value.Floor();
}

int64_t std::ceil(base::Seconds const &value)
{
	return value.Ceil();
}

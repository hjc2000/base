#include "Hz.h"
#include <base/unit/Seconds.h>

#pragma region 生命周期

base::Hz::Hz(Hz const &o)
{
	*this = o;
}

base::Hz::Hz(base::Fraction const &value)
{
	_value = value;
}

base::Hz::Hz(int64_t value)
{
	_value = value;
}

base::Hz::Hz(base::Seconds const &value)
{
	_value = static_cast<base::Fraction>(value).Reciprocal();
}

base::Hz &base::Hz::operator=(Hz const &o)
{
	_value = o._value;
	return *this;
}

#pragma endregion

#pragma region 重载全局运算符

std::ostream &operator<<(std::ostream &ostream, base::Hz const &right)
{
	ostream << static_cast<base::Fraction>(right);
	return ostream;
}

base::Hz operator+(int64_t left, base::Hz const &right)
{
	return left + static_cast<base::Fraction>(right);
}

base::Hz operator-(int64_t left, base::Hz const &right)
{
	return left - static_cast<base::Fraction>(right);
}

base::Hz operator*(int64_t left, base::Hz const &right)
{
	return left * static_cast<base::Fraction>(right);
}

base::Hz operator/(int64_t left, base::Hz const &right)
{
	return left / static_cast<base::Fraction>(right);
}

#pragma endregion

int64_t std::floor(base::Hz const &value)
{
	return value.Floor();
}

int64_t std::ceil(base::Hz const &value)
{
	return value.Ceil();
}

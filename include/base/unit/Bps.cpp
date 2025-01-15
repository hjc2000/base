#include "Bps.h"
#include <base/unit/Mbps.h>

#pragma region 生命周期

base::Bps::Bps(int64_t value)
{
	_value = value;
}

base::Bps::Bps(base::Fraction const &o)
{
	_value = o;
}

base::Bps::Bps(Mbps const &o)
{
	_value = static_cast<base::Fraction>(o) * 1000 * 1000;
}

base::Bps::Bps(Bps const &o)
{
	*this = o;
}

base::Bps &base::Bps::operator=(Bps const &o)
{
	_value = o._value;
	return *this;
}

#pragma endregion

#pragma region 重载全局运算符

std::ostream &operator<<(std::ostream &ostream, base::Bps const &right)
{
	ostream << static_cast<base::Fraction>(right);
	return ostream;
}

base::Bps operator+(int64_t left, base::Bps const &right)
{
	return left + static_cast<base::Fraction>(right);
}

base::Bps operator-(int64_t left, base::Bps const &right)
{
	return left - static_cast<base::Fraction>(right);
}

base::Bps operator*(int64_t left, base::Bps const &right)
{
	return left * static_cast<base::Fraction>(right);
}

base::Bps operator/(int64_t left, base::Bps const &right)
{
	return left / static_cast<base::Fraction>(right);
}

#pragma endregion

int64_t std::floor(base::Bps const &value)
{
	return value.Floor();
}

int64_t std::ceil(base::Bps const &value)
{
	return value.Ceil();
}

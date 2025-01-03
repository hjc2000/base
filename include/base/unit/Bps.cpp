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
	_value = o.Value() * 1000 * 1000;
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

#pragma region 四则运算符

base::Bps base::Bps::operator-() const
{
	return -_value;
}

base::Bps base::Bps::operator+(Bps const &value) const
{
	return _value + static_cast<base::Fraction>(value);
}

base::Bps base::Bps::operator-(Bps const &value) const
{
	return _value - static_cast<base::Fraction>(value);
}

base::Bps base::Bps::operator*(Bps const &value) const
{
	return _value * static_cast<base::Fraction>(value);
}

base::Bps base::Bps::operator/(Bps const &value) const
{
	return _value / static_cast<base::Fraction>(value);
}

base::Bps &base::Bps::operator+=(Bps const &value)
{
	_value += static_cast<base::Fraction>(value);
	return *this;
}

base::Bps &base::Bps::operator-=(Bps const &value)
{
	_value -= static_cast<base::Fraction>(value);
	return *this;
}

base::Bps &base::Bps::operator*=(Bps const &value)
{
	_value *= static_cast<base::Fraction>(value);
	return *this;
}

base::Bps &base::Bps::operator/=(Bps const &value)
{
	_value /= static_cast<base::Fraction>(value);
	return *this;
}

base::Bps base::Bps::operator+(base::Mbps const &value) const
{
	return *this + base::Bps{value};
}

base::Bps base::Bps::operator-(base::Mbps const &value) const
{
	return *this - base::Bps{value};
}

base::Bps base::Bps::operator*(base::Mbps const &value) const
{
	return *this * base::Bps{value};
}

base::Bps base::Bps::operator/(base::Mbps const &value) const
{
	return *this / base::Bps{value};
}

base::Bps &base::Bps::operator+=(base::Mbps const &value)
{
	*this += base::Bps{value};
	return *this;
}

base::Bps &base::Bps::operator-=(base::Mbps const &value)
{
	*this -= base::Bps{value};
	return *this;
}

base::Bps &base::Bps::operator*=(base::Mbps const &value)
{
	*this *= base::Bps{value};
	return *this;
}

base::Bps &base::Bps::operator/=(base::Mbps const &value)
{
	*this /= base::Bps{value};
	return *this;
}

#pragma endregion

#pragma region 比较运算符

bool base::Bps::operator==(Bps const &value) const
{
	return _value == value._value;
}

bool base::Bps::operator<(Bps const &value) const
{
	return _value < value._value;
}

bool base::Bps::operator>(Bps const &value) const
{
	return _value > value._value;
}

bool base::Bps::operator<=(Bps const &value) const
{
	return _value <= value._value;
}

bool base::Bps::operator>=(Bps const &value) const
{
	return _value >= value._value;
}

bool base::Bps::operator==(base::Mbps const &value) const
{
	return *this == base::Bps{value};
}

bool base::Bps::operator<(base::Mbps const &value) const
{
	return *this < base::Bps{value};
}

bool base::Bps::operator>(base::Mbps const &value) const
{
	return *this > base::Bps{value};
}

bool base::Bps::operator<=(base::Mbps const &value) const
{
	return *this <= base::Bps{value};
}

bool base::Bps::operator>=(base::Mbps const &value) const
{
	return *this >= base::Bps{value};
}

#pragma endregion

std::string base::Bps::ToString() const
{
	return _value.ToString();
}

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

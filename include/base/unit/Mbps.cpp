#include "Mbps.h"
#include <base/unit/Bps.h>

#pragma region 生命周期

base::Mbps::Mbps(int64_t value)
{
	_value = value;
}

base::Mbps::Mbps(base::Fraction const &o)
{
	_value = o;
}

base::Mbps::Mbps(Mbps const &o)
{
	*this = o;
}

base::Mbps::Mbps(base::Bps const &o)
{
	_value = o.Value() / 1000 / 1000;
}

base::Mbps &base::Mbps::operator=(Mbps const &o)
{
	_value = o._value;
	return *this;
}

#pragma endregion

#pragma region 四则运算符

base::Mbps base::Mbps::operator-() const
{
	return -_value;
}

base::Mbps base::Mbps::operator+(Mbps const &value) const
{
	return _value + static_cast<base::Fraction>(value);
}

base::Mbps base::Mbps::operator-(Mbps const &value) const
{
	return _value - static_cast<base::Fraction>(value);
}

base::Mbps base::Mbps::operator*(Mbps const &value) const
{
	return _value * static_cast<base::Fraction>(value);
}

base::Mbps base::Mbps::operator/(Mbps const &value) const
{
	return _value / static_cast<base::Fraction>(value);
}

base::Mbps &base::Mbps::operator+=(Mbps const &value)
{
	_value += static_cast<base::Fraction>(value);
	return *this;
}

base::Mbps &base::Mbps::operator-=(Mbps const &value)
{
	_value -= static_cast<base::Fraction>(value);
	return *this;
}

base::Mbps &base::Mbps::operator*=(Mbps const &value)
{
	_value *= static_cast<base::Fraction>(value);
	return *this;
}

base::Mbps &base::Mbps::operator/=(Mbps const &value)
{
	_value /= static_cast<base::Fraction>(value);
	return *this;
}

base::Mbps base::Mbps::operator+(base::Bps const &value) const
{
	return *this + base::Mbps{value};
}

base::Mbps base::Mbps::operator-(base::Bps const &value) const
{
	return *this - base::Mbps{value};
}

base::Mbps base::Mbps::operator*(base::Bps const &value) const
{
	return *this * base::Mbps{value};
}

base::Mbps base::Mbps::operator/(base::Bps const &value) const
{
	return *this / base::Mbps{value};
}

base::Mbps &base::Mbps::operator+=(base::Bps const &value)
{
	*this += base::Mbps{value};
	return *this;
}

base::Mbps &base::Mbps::operator-=(base::Bps const &value)
{
	*this -= base::Mbps{value};
	return *this;
}

base::Mbps &base::Mbps::operator*=(base::Bps const &value)
{
	*this *= base::Mbps{value};
	return *this;
}

base::Mbps &base::Mbps::operator/=(base::Bps const &value)
{
	*this /= base::Mbps{value};
	return *this;
}

#pragma endregion

#pragma region 比较运算符

bool base::Mbps::operator==(Mbps const &value) const
{
	return _value == value._value;
}

bool base::Mbps::operator<(Mbps const &value) const
{
	return _value < value._value;
}

bool base::Mbps::operator>(Mbps const &value) const
{
	return _value > value._value;
}

bool base::Mbps::operator<=(Mbps const &value) const
{
	return _value <= value._value;
}

bool base::Mbps::operator>=(Mbps const &value) const
{
	return _value >= value._value;
}

bool base::Mbps::operator==(base::Bps const &value) const
{
	return *this == base::Mbps{value};
}

bool base::Mbps::operator<(base::Bps const &value) const
{
	return *this < base::Mbps{value};
}

bool base::Mbps::operator>(base::Bps const &value) const
{
	return *this > base::Mbps{value};
}

bool base::Mbps::operator<=(base::Bps const &value) const
{
	return *this <= base::Mbps{value};
}

bool base::Mbps::operator>=(base::Bps const &value) const
{
	return *this >= base::Mbps{value};
}

#pragma endregion

std::string base::Mbps::ToString() const
{
	return _value.ToString();
}

#pragma region 重载全局运算符

std::ostream &operator<<(std::ostream &ostream, base::Mbps const &right)
{
	ostream << static_cast<base::Fraction>(right);
	return ostream;
}

base::Mbps operator+(int64_t left, base::Mbps const &right)
{
	return left + static_cast<base::Fraction>(right);
}

base::Mbps operator-(int64_t left, base::Mbps const &right)
{
	return left - static_cast<base::Fraction>(right);
}

base::Mbps operator*(int64_t left, base::Mbps const &right)
{
	return left * static_cast<base::Fraction>(right);
}

base::Mbps operator/(int64_t left, base::Mbps const &right)
{
	return left / static_cast<base::Fraction>(right);
}

#pragma endregion

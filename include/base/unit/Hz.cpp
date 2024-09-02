#include "Hz.h"
#include <base/unit/SecondPeriod.h>

base::Hz::Hz(Hz const &o)
{
    _value = o._value;
}

base::Hz::Hz(base::Fraction const &value)
{
    _value = value;
}

base::Hz::Hz(int64_t value)
{
    _value = value;
}

base::Hz::Hz(base::SecondPeriod const &value)
{
    _value = static_cast<base::Fraction>(value).Reciprocal();
}

base::Hz &base::Hz::operator=(Hz const &o)
{
    _value = o._value;
    return *this;
}

base::Hz base::Hz::operator-() const
{
    return -_value;
}

#pragma region 重载四则运算符

base::Hz base::Hz::operator+(Hz const &value) const
{
    return _value + static_cast<base::Fraction>(value);
}

base::Hz base::Hz::operator-(Hz const &value) const
{
    return _value - static_cast<base::Fraction>(value);
}

base::Hz base::Hz::operator*(Hz const &value) const
{
    return _value * static_cast<base::Fraction>(value);
}

base::Hz base::Hz::operator/(Hz const &value) const
{
    return _value / static_cast<base::Fraction>(value);
}

#pragma endregion

#pragma region 重载自改变四则运算符

base::Hz &base::Hz::operator+=(Hz const &value)
{
    _value += static_cast<base::Fraction>(value);
    return *this;
}

base::Hz &base::Hz::operator-=(Hz const &value)
{
    _value -= static_cast<base::Fraction>(value);
    return *this;
}

base::Hz &base::Hz::operator*=(Hz const &value)
{
    _value *= static_cast<base::Fraction>(value);
    return *this;
}

base::Hz &base::Hz::operator/=(Hz const &value)
{
    _value /= static_cast<base::Fraction>(value);
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

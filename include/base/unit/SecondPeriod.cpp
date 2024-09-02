#include "SecondPeriod.h"
#include <base/unit/Hz.h>

base::SecondPeriod::SecondPeriod(SecondPeriod const &o)
{
    _value = o._value;
}

base::SecondPeriod::SecondPeriod(base::Fraction const &value)
{
    _value = value;
}

base::SecondPeriod::SecondPeriod(int64_t value)
{
    _value = value;
}

base::SecondPeriod::SecondPeriod(base::Hz const &value)
{
    _value = static_cast<base::Fraction>(value).Reciprocal();
}

base::SecondPeriod &base::SecondPeriod::operator=(SecondPeriod const &o)
{
    _value = o._value;
    return *this;
}

base::SecondPeriod base::SecondPeriod::operator-() const
{
    return -_value;
}

#pragma region 重载四则运算符

base::SecondPeriod base::SecondPeriod::operator+(SecondPeriod const &value) const
{
    return _value + static_cast<base::Fraction>(value);
}

base::SecondPeriod base::SecondPeriod::operator-(SecondPeriod const &value) const
{
    return _value - static_cast<base::Fraction>(value);
}

base::SecondPeriod base::SecondPeriod::operator*(SecondPeriod const &value) const
{
    return _value * static_cast<base::Fraction>(value);
}

base::SecondPeriod base::SecondPeriod::operator/(SecondPeriod const &value) const
{
    return _value / static_cast<base::Fraction>(value);
}

#pragma endregion

#pragma region 重载自改变四则运算符

base::SecondPeriod &base::SecondPeriod::operator+=(SecondPeriod const &value)
{
    _value += static_cast<base::Fraction>(value);
    return *this;
}

base::SecondPeriod &base::SecondPeriod::operator-=(SecondPeriod const &value)
{
    _value -= static_cast<base::Fraction>(value);
    return *this;
}

base::SecondPeriod &base::SecondPeriod::operator*=(SecondPeriod const &value)
{
    _value *= static_cast<base::Fraction>(value);
    return *this;
}

base::SecondPeriod &base::SecondPeriod::operator/=(SecondPeriod const &value)
{
    _value /= static_cast<base::Fraction>(value);
    return *this;
}

#pragma endregion

#pragma region 重载全局运算符

std::ostream &operator<<(std::ostream &ostream, base::SecondPeriod const &right)
{
    ostream << static_cast<base::Fraction>(right);
    return ostream;
}

base::SecondPeriod operator+(int64_t left, base::SecondPeriod const &right)
{
    return left + static_cast<base::Fraction>(right);
}

base::SecondPeriod operator-(int64_t left, base::SecondPeriod const &right)
{
    return left - static_cast<base::Fraction>(right);
}

base::SecondPeriod operator*(int64_t left, base::SecondPeriod const &right)
{
    return left * static_cast<base::Fraction>(right);
}

base::SecondPeriod operator/(int64_t left, base::SecondPeriod const &right)
{
    return left / static_cast<base::Fraction>(right);
}

#pragma endregion

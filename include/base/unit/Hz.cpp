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

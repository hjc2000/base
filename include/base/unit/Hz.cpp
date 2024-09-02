#include "Hz.h"
#include <base/unit/Period.h>

base::Hz::Hz(base::Fraction const &value)
{
    _value = value;
}

base::Hz::Hz(int64_t value)
{
    _value = value;
}

base::Hz::Hz(base::Period const &value)
{
    _value = static_cast<base::Fraction>(value).Reciprocal();
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

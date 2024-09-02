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
    _value = value.Value().Reciprocal();
}

base::Hz base::Hz::operator-() const
{
    return -_value;
}

base::Hz base::Hz::operator+(Hz const &value) const
{
    return _value + value.Value();
}

base::Hz base::Hz::operator-(Hz const &value) const
{
    return _value - value.Value();
}

base::Hz base::Hz::operator*(Hz const &value) const
{
    return _value * value.Value();
}

base::Hz base::Hz::operator/(Hz const &value) const
{
    return _value / value.Value();
}

base::Hz &base::Hz::operator+=(Hz const &value)
{
    _value += value.Value();
    return *this;
}

base::Hz &base::Hz::operator-=(Hz const &value)
{
    _value -= value.Value();
    return *this;
}

base::Hz &base::Hz::operator*=(Hz const &value)
{
    _value *= value.Value();
    return *this;
}

base::Hz &base::Hz::operator/=(Hz const &value)
{
    _value /= value.Value();
    return *this;
}

#include "Period.h"
#include <base/unit/Hz.h>

base::Period::Period(base::Fraction const &value)
{
    _value = value;
}

base::Period::Period(int64_t value)
{
    _value = value;
}

base::Period::Period(base::Hz const &value)
{
    _value = value.Value().Reciprocal();
}

base::Period base::Period::operator-() const
{
    return -_value;
}

base::Period base::Period::operator+(Period const &value) const
{
    return _value + value.Value();
}

base::Period base::Period::operator-(Period const &value) const
{
    return _value - value.Value();
}

base::Period base::Period::operator*(Period const &value) const
{
    return _value * value.Value();
}

base::Period base::Period::operator/(Period const &value) const
{
    return _value / value.Value();
}

base::Period &base::Period::operator+=(Period const &value)
{
    _value += value.Value();
    return *this;
}

base::Period &base::Period::operator-=(Period const &value)
{
    _value -= value.Value();
    return *this;
}

base::Period &base::Period::operator*=(Period const &value)
{
    _value *= value.Value();
    return *this;
}

base::Period &base::Period::operator/=(Period const &value)
{
    _value /= value.Value();
    return *this;
}

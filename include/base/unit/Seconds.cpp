#include "Seconds.h"
#include <base/unit/Hz.h>

base::Seconds::Seconds(Seconds const &o)
{
    _value = o._value;
}

base::Seconds::Seconds(base::Fraction const &value)
{
    _value = value;
}

base::Seconds::Seconds(int64_t value)
{
    _value = value;
}

base::Seconds::Seconds(base::Hz const &value)
{
    _value = static_cast<base::Fraction>(value).Reciprocal();
}

base::Seconds::Seconds(std::chrono::seconds const &value)
{
    _value = value.count();
}

base::Seconds::Seconds(std::chrono::milliseconds const &value)
{
    _value = base::Fraction{value.count()} / 1000;
}

base::Seconds::Seconds(std::chrono::microseconds const &value)
{
    _value = base::Fraction{value.count()} / 1000 / 1000;
}

base::Seconds &base::Seconds::operator=(Seconds const &o)
{
    _value = o._value;
    return *this;
}

base::Seconds::operator base::Fraction() const
{
    return _value;
}

base::Seconds::operator std::chrono::seconds() const
{
    return std::chrono::seconds{static_cast<int64_t>(_value)};
}

base::Seconds::operator std::chrono::milliseconds() const
{
    return std::chrono::milliseconds{static_cast<int64_t>(_value * 1000)};
}

base::Seconds::operator std::chrono::microseconds() const
{
    return std::chrono::microseconds{static_cast<int64_t>(_value * 1000 * 1000)};
}

base::Seconds base::Seconds::operator-() const
{
    return -_value;
}

#pragma region 重载四则运算符

base::Seconds base::Seconds::operator+(Seconds const &value) const
{
    return _value + static_cast<base::Fraction>(value);
}

base::Seconds base::Seconds::operator-(Seconds const &value) const
{
    return _value - static_cast<base::Fraction>(value);
}

base::Seconds base::Seconds::operator*(Seconds const &value) const
{
    return _value * static_cast<base::Fraction>(value);
}

base::Seconds base::Seconds::operator/(Seconds const &value) const
{
    return _value / static_cast<base::Fraction>(value);
}

#pragma endregion

#pragma region 重载自改变四则运算符

base::Seconds &base::Seconds::operator+=(Seconds const &value)
{
    _value += static_cast<base::Fraction>(value);
    return *this;
}

base::Seconds &base::Seconds::operator-=(Seconds const &value)
{
    _value -= static_cast<base::Fraction>(value);
    return *this;
}

base::Seconds &base::Seconds::operator*=(Seconds const &value)
{
    _value *= static_cast<base::Fraction>(value);
    return *this;
}

base::Seconds &base::Seconds::operator/=(Seconds const &value)
{
    _value /= static_cast<base::Fraction>(value);
    return *this;
}

#pragma endregion

#pragma region 重载全局运算符

std::ostream &operator<<(std::ostream &ostream, base::Seconds const &right)
{
    ostream << static_cast<base::Fraction>(right);
    return ostream;
}

base::Seconds operator+(int64_t left, base::Seconds const &right)
{
    return left + static_cast<base::Fraction>(right);
}

base::Seconds operator-(int64_t left, base::Seconds const &right)
{
    return left - static_cast<base::Fraction>(right);
}

base::Seconds operator*(int64_t left, base::Seconds const &right)
{
    return left * static_cast<base::Fraction>(right);
}

base::Seconds operator/(int64_t left, base::Seconds const &right)
{
    return left / static_cast<base::Fraction>(right);
}

#pragma endregion

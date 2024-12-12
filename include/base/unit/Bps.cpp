#include "Bps.h"

base::Bps::Bps(int64_t value)
{
    _value = value;
}

base::Bps::Bps(base::Fraction const &o)
{
    _value = o;
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

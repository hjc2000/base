#include "Mbps.h"
#include <base/unit/Bps.h>

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

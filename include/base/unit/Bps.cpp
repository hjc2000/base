#include "Bps.h"

base::Bps::Bps(int64_t value)
{
    _value = value;
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

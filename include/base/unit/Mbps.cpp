#include "Mbps.h"

base::Mbps::Mbps(int64_t value)
{
    _value = value;
}

base::Mbps::Mbps(Mbps const &o)
{
    *this = o;
}

base::Mbps &base::Mbps::operator=(Mbps const &o)
{
    _value = o._value;
    return *this;
}

#include "Bps.h"
#include <base/unit/Mbps.h>

base::Bps::Bps(int64_t value)
{
	_value = value;
}

base::Bps::Bps(base::Fraction const &o)
{
	_value = o;
}

base::Bps::Bps(Mbps const &o)
{
	_value = static_cast<base::Fraction>(o) * 1000 * 1000;
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

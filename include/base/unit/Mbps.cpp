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
	_value = static_cast<base::Fraction>(o) / 1000 / 1000;
}

base::Mbps &base::Mbps::operator=(Mbps const &o)
{
	_value = o._value;
	return *this;
}

std::string base::Mbps::UnitString() const
{
	return "Mbps";
}

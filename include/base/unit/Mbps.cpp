#include "Mbps.h"
#include "base/unit/bps.h"

base::Mbps::Mbps(base::Fraction const &o)
{
	_value = o;
}

base::Mbps::Mbps(base::bps const &o)
{
	_value = static_cast<base::Fraction>(o) / 1000 / 1000;
}

std::string base::Mbps::UnitString() const
{
	return "Mbps";
}

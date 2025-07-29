#include "Mbps.h"
#include "base/unit/bps.h"

base::unit::Mbps::Mbps(base::Fraction const &o)
{
	_value = o;
}

base::unit::Mbps::Mbps(base::unit::bps const &o)
{
	_value = static_cast<base::Fraction>(o) / 1000 / 1000;
}

std::string base::unit::Mbps::UnitString() const
{
	return "Mbps";
}

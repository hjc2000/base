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

std::string base::Bps::UnitString() const
{
	return "bps";
}

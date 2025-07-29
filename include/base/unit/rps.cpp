#include "rps.h"
#include "rpm.h"

base::unit::rps::rps(base::Fraction const &value)
{
	_value = value;
}

base::unit::rps::rps(base::unit::rpm const &value)
{
	_value = value.Value() / 60;
}

base::Fraction &base::unit::rps::Value()
{
	return _value;
}

std::string base::unit::rps::UnitString() const
{
	return "rps";
}

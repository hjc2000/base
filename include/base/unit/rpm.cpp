#include "rpm.h"
#include "rps.h"

base::unit::rpm::rpm(base::Fraction const &value)
{
	_value = value;
}

base::unit::rpm::rpm(base::unit::rps const &value)
{
	_value = value.Value() * 60;
}

base::Fraction &base::unit::rpm::Value()
{
	return _value;
}

std::string base::unit::rpm::UnitString() const
{
	return "rpm";
}

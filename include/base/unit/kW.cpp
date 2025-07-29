#include "kW.h"
#include "W.h"

base::unit::kW::kW(base::unit::W const &value)
{
	_value = value.Value() / 1000;
}

base::Fraction &base::unit::kW::Value()
{
	return _value;
}

std::string base::unit::kW::UnitString() const
{
	return "kW";
}

#include "kW.h"
#include "W.h"

base::kW::kW(base::W const &value)
{
	_value = value.Value() / 1000;
}

base::Fraction &base::kW::Value()
{
	return _value;
}

std::string base::kW::UnitString() const
{
	return "kW";
}

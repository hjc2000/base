#include "W.h"
#include "kW.h"

base::unit::W::W(base::unit::kW const &value)
{
	_value = value.Value() * 1000;
}

base::Fraction &base::unit::W::Value()
{
	return _value;
}

std::string base::unit::W::UnitString() const
{
	return "W";
}

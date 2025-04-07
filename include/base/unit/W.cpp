#include "W.h"
#include "kW.h"

base::W::W(base::kW const &value)
{
	_value = value.Value() * 1000;
}

base::Fraction &base::W::Value()
{
	return _value;
}

std::string base::W::UnitString() const
{
	return "W";
}

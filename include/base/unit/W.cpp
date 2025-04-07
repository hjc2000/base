#include "W.h"

base::Fraction &base::W::Value()
{
	return _value;
}

std::string base::W::UnitString() const
{
	return "W";
}

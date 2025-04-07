#include "V.h"

base::Fraction &base::V::Value()
{
	return _value;
}

std::string base::V::UnitString() const
{
	return "V";
}

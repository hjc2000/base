#include "Celsius.h"

base::Fraction &base::Celsius::Value()
{
	return _value;
}

std::string base::Celsius::UnitString() const
{
	return "℃";
}

#include "A.h"

base::Fraction &base::A::Value()
{
	return _value;
}

std::string base::A::UnitString() const
{
	return "A";
}

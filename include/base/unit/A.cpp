#include "A.h"

base::A::A(int64_t value)
{
	_value = value;
}

base::A::A(base::Fraction const &value)
{
	_value = value;
}

base::Fraction &base::A::Value()
{
	return _value;
}

std::string base::A::UnitString() const
{
	return "A";
}

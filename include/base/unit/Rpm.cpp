#include "Rpm.h"
#include "Rps.h"

base::Rpm::Rpm(int64_t value)
{
	_value = value;
}

base::Rpm::Rpm(base::Fraction const &value)
{
	_value = value;
}

base::Rpm::Rpm(base::Rps const &value)
{
	_value = value.Value() * 60;
}

base::Fraction &base::Rpm::Value()
{
	return _value;
}

std::string base::Rpm::UnitString() const
{
	return "rpm";
}

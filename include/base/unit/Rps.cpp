#include "Rps.h"
#include "Rpm.h"

base::Rps::Rps(int64_t value)
{
	_value = value;
}

base::Rps::Rps(base::Fraction const &value)
{
	_value = value;
}

base::Rps::Rps(base::Rpm const &value)
{
	_value = value.Value() / 60;
}

base::Fraction &base::Rps::Value()
{
	return _value;
}

std::string base::Rps::UnitString() const
{
	return "rps";
}

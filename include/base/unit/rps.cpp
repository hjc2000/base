#include "rps.h"
#include "rpm.h"

base::rps::rps(int64_t value)
{
	_value = value;
}

base::rps::rps(base::Fraction const &value)
{
	_value = value;
}

base::rps::rps(base::rpm const &value)
{
	_value = value.Value() / 60;
}

base::Fraction &base::rps::Value()
{
	return _value;
}

std::string base::rps::UnitString() const
{
	return "rps";
}

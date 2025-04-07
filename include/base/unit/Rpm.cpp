#include "rpm.h"
#include "Rps.h"

base::rpm::rpm(int64_t value)
{
	_value = value;
}

base::rpm::rpm(base::Fraction const &value)
{
	_value = value;
}

base::rpm::rpm(base::Rps const &value)
{
	_value = value.Value() * 60;
}

base::Fraction &base::rpm::Value()
{
	return _value;
}

std::string base::rpm::UnitString() const
{
	return "rpm";
}

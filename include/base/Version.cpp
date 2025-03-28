#include "Version.h"

base::Version &base::Version::operator++()
{
	++_value;
	return *this;
}

base::Version base::Version::operator++(int)
{
	Version ret{*this};
	++(*this);
	return ret;
}

uint64_t base::Version::Value() const
{
	return _value;
}

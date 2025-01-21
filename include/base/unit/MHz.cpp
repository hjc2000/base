#include "MHz.h"
#include <base/unit/Hz.h>
#include <base/unit/Seconds.h>

base::MHz::MHz(MHz const &o)
{
	*this = o;
}

base::MHz::MHz(base::Fraction const &value)
{
	_value = value;
}

base::MHz::MHz(base::Hz const &value)
{
	_value = static_cast<base::Fraction>(value) / 1000 / 1000;
}

base::MHz::MHz(int64_t value)
{
	_value = value;
}

base::MHz::MHz(base::Seconds const &value)
	: MHz(base::Hz{value})
{
}

base::MHz &base::MHz::operator=(MHz const &o)
{
	_value = o._value;
	return *this;
}

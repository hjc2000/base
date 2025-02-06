#include "Nanoseconds.h"
#include <base/unit/Hz.h>
#include <base/unit/MHz.h>
#include <base/unit/Seconds.h>

base::Nanoseconds::Nanoseconds(Nanoseconds const &o)
{
	*this = o;
}

base::Nanoseconds::Nanoseconds(base::Fraction const &value)
{
	_value = value;
}

base::Nanoseconds::Nanoseconds(int64_t value)
{
	_value = value;
}

base::Nanoseconds::Nanoseconds(base::Seconds const &value)
{
	_value = static_cast<base::Fraction>(value) * 1000 * 1000 * 1000;
}

base::Nanoseconds::Nanoseconds(base::Hz const &value)
	: Nanoseconds{base::Seconds{value}}
{
}

base::Nanoseconds::Nanoseconds(base::MHz const &value)
	: Nanoseconds(base::Seconds{value})
{
}

base::Nanoseconds::Nanoseconds(std::chrono::seconds const &value)
	: Nanoseconds(base::Seconds{value})
{
}

base::Nanoseconds::Nanoseconds(std::chrono::milliseconds const &value)
	: Nanoseconds(base::Seconds{value})
{
}

base::Nanoseconds::Nanoseconds(std::chrono::microseconds const &value)
	: Nanoseconds(base::Seconds{value})
{
}

base::Nanoseconds &base::Nanoseconds::operator=(Nanoseconds const &o)
{
	_value = o._value;
	return *this;
}

std::string base::Nanoseconds::UnitString() const
{
	return "ns";
}

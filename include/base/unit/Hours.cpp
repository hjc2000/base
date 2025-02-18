#include "Hours.h"
#include <base/unit/Days.h>
#include <base/unit/Minutes.h>

base::Hours::Hours(base::Fraction const &value)
{
	_value = value;
}

base::Hours::Hours(int64_t value)
{
	_value = value;
}

base::Hours::Hours(base::Days const &value)
{
	_value = static_cast<base::Fraction>(value) * 24;
}

base::Hours::Hours(base::Minutes const &value)
{
	_value = static_cast<base::Fraction>(value) / 60;
}

base::Hours::Hours(base::Seconds const &value)
	: Hours(base::Minutes{value})
{
}

base::Hours::Hours(base::Nanoseconds const &value)
	: Hours(base::Minutes{value})
{
}

base::Hours::Hours(base::Hz const &value)
	: Hours(base::Minutes{value})
{
}

base::Hours::Hours(base::MHz const &value)
	: Hours(base::Minutes{value})
{
}

base::Hours::Hours(std::chrono::seconds const &value)
	: Hours(base::Minutes{value})
{
}

base::Hours::Hours(std::chrono::milliseconds const &value)
	: Hours(base::Minutes{value})
{
}

base::Hours::Hours(std::chrono::microseconds const &value)
	: Hours(base::Minutes{value})
{
}

std::string base::Hours::UnitString() const
{
	return "h";
}

base::Hours::operator std::chrono::seconds() const
{
	return std::chrono::seconds{base::Minutes{*this}};
}

base::Hours::operator std::chrono::milliseconds() const
{
	return std::chrono::seconds{base::Minutes{*this}};
}

base::Hours::operator std::chrono::microseconds() const
{
	return std::chrono::seconds{base::Minutes{*this}};
}

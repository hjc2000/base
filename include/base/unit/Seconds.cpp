#include "Seconds.h"
#include "base/unit/Hours.h"
#include "base/unit/Hz.h"
#include "base/unit/Minutes.h"
#include "base/unit/Nanoseconds.h"
#include <chrono>

base::Seconds::Seconds(base::Fraction const &value)
{
	_value = value;
}

base::Seconds::Seconds(int64_t value)
{
	_value = value;
}

base::Seconds::Seconds(base::Hours const &value)
{
	_value = static_cast<base::Fraction>(value) * 60 * 60;
}

base::Seconds::Seconds(base::Minutes const &value)
{
	_value = static_cast<base::Fraction>(value) * 60;
}

base::Seconds::Seconds(base::Nanoseconds const &value)
{
	_value = static_cast<base::Fraction>(value) / 1000 / 1000 / 1000;
}

base::Seconds::Seconds(base::Hz const &value)
{
	_value = static_cast<base::Fraction>(value).Reciprocal();
}

base::Seconds::Seconds(base::MHz const &value)
	: Seconds(base::Hz{value})
{
}

base::Seconds::Seconds(std::chrono::seconds const &value)
{
	_value = base::Fraction{value.count()};
}

base::Seconds::Seconds(std::chrono::milliseconds const &value)
{
	_value = base::Fraction{value.count()} / 1000;
}

base::Seconds::Seconds(std::chrono::microseconds const &value)
{
	_value = base::Fraction{value.count()} / 1000 / 1000;
}

base::Seconds::Seconds(std::chrono::nanoseconds const &value)
{
	_value = base::Fraction{value.count()} / 1000 / 1000 / 1000;
}

std::string base::Seconds::UnitString() const
{
	return "s";
}

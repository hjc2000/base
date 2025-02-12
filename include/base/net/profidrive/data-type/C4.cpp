#include "C4.h"

base::C4::C4(base::Fraction const &value)
{
	base::Fraction factor = base::Fraction{10000, value.Den()};
	_value = static_cast<int64_t>(value.Num() * factor);
}

base::C4::operator base::Fraction() const
{
	return _value * base::Fraction{_value, 10000};
}

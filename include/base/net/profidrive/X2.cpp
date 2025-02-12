#include "X2.h"

base::X2::X2(base::Fraction const &value)
{
	base::Fraction factor = base::Fraction{static_cast<int64_t>(1 << 12), value.Den()};
	_value = static_cast<int64_t>(value.Num() * factor);
}

base::X2::operator base::Fraction() const
{
	int64_t den = static_cast<int64_t>(1 << 12);
	return _value * base::Fraction{_value, den};
}

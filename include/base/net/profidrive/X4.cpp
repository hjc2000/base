#include "X4.h"

base::X4::X4(base::Fraction const &value)
{
	base::Fraction factor = base::Fraction{static_cast<int64_t>(1 << 28), value.Den()};
	_value = static_cast<int64_t>(value.Num() * factor);
}

base::X4::operator base::Fraction() const
{
	int64_t den = static_cast<int64_t>(1 << 28);
	return _value * base::Fraction{_value, den};
}

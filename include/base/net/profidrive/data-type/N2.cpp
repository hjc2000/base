#include "N2.h"

base::N2::N2(base::Fraction const &value)
{
	// 1 左移 14 位就是 2^14.
	base::Fraction factor = base::Fraction{static_cast<int64_t>(1 << 14), value.Den()};
	_value = static_cast<int64_t>(value.Num() * factor);
}

base::N2::operator base::Fraction() const
{
	// 1 左移 14 位就是 2^14.
	int64_t den = static_cast<int64_t>(1 << 14);
	return _value * base::Fraction{_value, den};
}

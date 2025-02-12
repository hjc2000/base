#include "N4.h"

base::N4::N4(base::Fraction const &value)
{
	// 1 左移 30 位就是 2^30.
	base::Fraction factor = base::Fraction{static_cast<int64_t>(1 << 30), value.Den()};
	_value = static_cast<int64_t>(value.Num() * factor);
}

base::N4::operator base::Fraction() const
{
	// 1 左移 30 位就是 2^30.
	int64_t den = static_cast<int64_t>(1 << 30);
	return _value * base::Fraction{_value, den};
}

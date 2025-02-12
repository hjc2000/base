#include "IProfidriveNumber.h"

void base::IProfidriveNumber::From(base::ReadOnlySpan const &span)
{
	Span().CopyFrom(span);
}

void base::IProfidriveNumber::From(base::Fraction const &value)
{
	base::Fraction factor = base::Fraction{Factor(), value.Den()};

	_converter.GetBytes(static_cast<int32_t>(value.Num() * factor),
						Span());
}

base::IProfidriveNumber::operator base::Fraction() const
{
	int32_t value = _converter.ToInt32(Span());
	return value * base::Fraction{value, Factor()};
}

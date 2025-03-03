#include "C4.h"

base::C4::C4(base::ReadOnlySpan const &value)
{
	From(value);
}

base::C4::C4(base::Fraction const &value)
{
	From(value);
}

int32_t base::C4::Factor() const
{
	return 10000;
}

base::Span base::C4::Span()
{
	return _buffer.AsArraySpan();
}

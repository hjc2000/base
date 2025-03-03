#include "N2.h"

base::N2::N2(base::ReadOnlySpan const &value)
{
	From(value);
}

base::N2::N2(base::Fraction const &value)
{
	From(value);
}

int32_t base::N2::Factor() const
{
	return static_cast<int64_t>(1 << 14);
}

base::Span base::N2::Span()
{
	return _buffer.AsArraySpan();
}

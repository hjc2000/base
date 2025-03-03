#include "X2.h"

base::X2::X2(base::ReadOnlySpan const &value)
{
	From(value);
}

base::X2::X2(base::Fraction const &value)
{
	From(value);
}

int32_t base::X2::Factor() const
{
	return static_cast<int64_t>(1 << 12);
}

base::Span base::X2::Span()
{
	return _buffer.AsArraySpan();
}

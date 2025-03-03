#include "X4.h"

base::X4::X4(base::ReadOnlySpan const &value)
{
	From(value);
}

base::X4::X4(base::Fraction const &value)
{
	From(value);
}

int32_t base::X4::Factor() const
{
	return static_cast<int64_t>(1 << 28);
}

base::Span base::X4::Span()
{
	return _buffer.AsArraySpan();
}

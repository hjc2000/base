#include "N4.h"

base::N4::N4(base::ReadOnlySpan const &value)
{
	From(value);
}

base::N4::N4(base::Fraction const &value)
{
	From(value);
}

int32_t base::N4::Factor() const
{
	// 2 的 30 次方
	return static_cast<int64_t>(1 << 30);
}

base::Span base::N4::Span()
{
	return _buffer.AsArraySpan();
}

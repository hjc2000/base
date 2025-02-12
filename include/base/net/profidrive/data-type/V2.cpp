#include "V2.h"

base::V2::V2(base::ReadOnlySpan const &span)
{
	Span().CopyFrom(span);
}

base::V2::V2(std::bitset<16> const &set)
{
	uint16_t data = set.to_ulong();
	_converter.GetBytes(data, _buffer.AsArraySpan());
}

base::V2::operator std::bitset<16>() const
{
	std::bitset<16> set{};
	uint16_t data = _converter.ToUInt16(_buffer.AsReadOnlyArraySpan());
	for (int i = 0; i < 16; i++)
	{
		set[i] = data & (1 << i);
	}

	return set;
}

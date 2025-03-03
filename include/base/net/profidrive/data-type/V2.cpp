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

std::bitset<16> base::V2::ToBitSet() const
{
	std::bitset<16> set{};

	// 经过转换后，变成小端序了，第 1 个字节是 bit0 到 bit7，第 2 个字节是 bit8 到 bit15.
	uint16_t data = _converter.ToUInt16(_buffer.AsReadOnlyArraySpan());
	for (int i = 0; i < 16; i++)
	{
		set[i] = data & (1 << i);
	}

	return set;
}

base::V2::operator std::bitset<16>() const
{
	return ToBitSet();
}

base::Span base::V2::Span()
{
	return _buffer.AsArraySpan();
}

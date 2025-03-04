#include "V2.h"

base::profidrive::V2::V2(base::ReadOnlySpan const &span)
{
	Span().CopyFrom(span);
}

base::profidrive::V2::V2(std::bitset<16> const &set)
{
	uint16_t data = set.to_ulong();
	_converter.GetBytes(data, _buffer.Span());
}

base::profidrive::V2::operator std::bitset<16>() const
{
	return ToBitSet();
}

std::bitset<16> base::profidrive::V2::ToBitSet() const
{
	std::bitset<16> set{};

	// 经过转换后，变成小端序了，第 1 个字节是 bit0 到 bit7，第 2 个字节是 bit8 到 bit15.
	uint16_t data = _converter.ToUInt16(_buffer.Span());
	for (int i = 0; i < 16; i++)
	{
		set[i] = data & (1 << i);
	}

	return set;
}

base::Span base::profidrive::V2::Span()
{
	return _buffer.Span();
}

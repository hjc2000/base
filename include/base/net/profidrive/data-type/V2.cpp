#include "V2.h"

base::profidrive::V2::V2(base::ReadOnlySpan const &span)
{
	// 经过转换后，变成小端序了，第 1 个字节是 bit0 到 bit7，第 2 个字节是 bit8 到 bit15.
	uint16_t data = _converter.ToUInt16(span);
	for (int i = 0; i < 16; i++)
	{
		_bitset[i] = data & (1 << i);
	}
}

base::profidrive::V2::V2(std::bitset<16> const &set)
{
	_bitset = set;
}

base::profidrive::V2::operator std::bitset<16>() const
{
	return _bitset;
}

base::Array<uint8_t, 2> base::profidrive::V2::BufferForSending() const
{
	uint16_t data = _bitset.to_ulong();
	base::Array<uint8_t, 2> buffer;
	_converter.GetBytes(data, buffer.Span());
	return buffer;
}

auto base::profidrive::V2::operator[](int32_t index) -> decltype(_bitset[index])
{
	auto ret = _bitset[index];
	return ret;
}

auto base::profidrive::V2::operator[](int32_t index) const -> decltype(_bitset[index])
{
	return _bitset[index];
}

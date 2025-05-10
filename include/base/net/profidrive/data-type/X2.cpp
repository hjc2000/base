#include "X2.h"

base::profidrive::X2::operator base::Fraction() const
{
	return _value;
}

base::Array<uint8_t, 2> base::profidrive::X2::BufferForSending() const
{
	// 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
	// 放大后截断为整型。
	int16_t x2 = static_cast<int16_t>(_value * Factor());

	base::Array<uint8_t, 2> buffer;
	_converter.GetBytes(x2, buffer.Span());
	return buffer;
}

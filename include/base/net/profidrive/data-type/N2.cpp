#include "N2.h"

int32_t base::profidrive::N2::Factor() const
{
	return static_cast<int64_t>(1 << 14);
}

base::profidrive::N2::N2(base::ReadOnlySpan const &span)
{
	// 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
	// 放大后截断为整型。
	//
	// 想要获得分数的实际值，就将这个整型除以 Factor.
	int16_t n2 = _converter.FromBytes<int16_t>(span);
	_value = base::Fraction{n2, Factor()};
}

base::profidrive::N2::N2(base::Fraction const &value)
{
	_value = value;
}

base::profidrive::N2::operator base::Fraction() const
{
	return _value;
}

base::Array<uint8_t, 2> base::profidrive::N2::BufferForSending() const
{
	// 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
	// 放大后截断为整型。
	int16_t n2 = static_cast<int16_t>(_value * Factor());

	base::Array<uint8_t, 2> buffer;
	_converter.GetBytes(n2, buffer.Span());
	return buffer;
}

#include "C4.h"

int32_t base::profidrive::C4::Factor() const
{
	return 10000;
}

base::profidrive::C4::C4(base::ReadOnlySpan const &span)
{
	/* 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
	 * 放大后截断为整型。
	 *
	 * 想要获得分数的实际值，就将这个整型除以 Factor.
	 */
	int32_t c4 = _converter.ToInt32(span);
	_value = base::Fraction{c4, Factor()};
}

base::profidrive::C4::C4(base::Fraction const &value)
{
	_value = value;
}

base::profidrive::C4::operator base::Fraction() const
{
	return _value;
}

base::Array<uint8_t, 4> base::profidrive::C4::BufferForSending() const
{
	/* 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
	 * 放大后截断为整型。
	 */
	int32_t c4 = static_cast<int32_t>(_value * Factor());

	base::Array<uint8_t, 4> buffer;
	_converter.GetBytes(c4, buffer.Span());
	return buffer;
}

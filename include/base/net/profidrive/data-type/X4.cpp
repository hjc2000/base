#include "X4.h"

int32_t base::profidrive::X4::Factor() const
{
	return static_cast<int64_t>(1 << 28);
}

base::profidrive::X4::X4(base::ReadOnlySpan const &span)
{
	/* 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
	 * 放大后截断为整型。
	 *
	 * 想要获得分数的实际值，就将这个整型除以 Factor.
	 */
	int32_t x4 = _converter.FromBytes<int32_t>(span);
	_value = base::Fraction{x4, Factor()};
}

base::profidrive::X4::X4(base::Fraction const &value)
{
	_value = value;
}

base::profidrive::X4::operator base::Fraction() const
{
	return _value;
}

base::Array<uint8_t, 4> base::profidrive::X4::BufferForSending() const
{
	/* 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
	 * 放大后截断为整型。
	 */
	int32_t x4 = static_cast<int32_t>(_value * Factor());

	base::Array<uint8_t, 4> buffer;
	_converter.GetBytes(x4, buffer.Span());
	return buffer;
}

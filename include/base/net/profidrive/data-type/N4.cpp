#include "N4.h"

int32_t base::profidrive::N4::Factor() const
{
	// 2 的 30 次方
	return static_cast<int64_t>(1 << 30);
}

base::profidrive::N4::N4(base::ReadOnlySpan const &span)
{
	/* 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
	 * 放大后截断为整型。
	 *
	 * 想要获得分数的实际值，就将这个整型除以 Factor.
	 */
	int32_t n4 = _converter.ToInt32(span);
	_value = base::Fraction{n4, Factor()};
}

base::profidrive::N4::N4(base::Fraction const &value)
{
	_value = value;
}

base::profidrive::N4::operator base::Fraction() const
{
	return _value;
}

base::Array<uint8_t, 4> base::profidrive::N4::BufferForSending() const
{
	/* 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
	 * 放大后截断为整型。
	 */
	int32_t n4 = static_cast<int32_t>(_value * Factor());

	base::Array<uint8_t, 4> buffer;
	_converter.GetBytes(n4, buffer.Span());
	return buffer;
}

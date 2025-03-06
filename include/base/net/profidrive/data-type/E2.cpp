#include "E2.h"

int32_t base::profidrive::E2::Factor() const
{
	return static_cast<int64_t>(1 << 7);
}

base::profidrive::E2::E2(base::ReadOnlySpan const &value)
{
	Span().CopyFrom(value);
}

base::profidrive::E2::E2(base::Fraction const &value)
{
	/* 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
	 * 放大后截断为整型。
	 */
	int16_t result = static_cast<int16_t>(value * Factor());

	// 得到整型后要转换为大端序。
	_converter.GetBytes(result, Span());
}

base::Span base::profidrive::E2::Span()
{
	return _buffer.AsArraySpan();
}

base::ReadOnlySpan base::profidrive::E2::Span() const
{
	return const_cast<E2 *>(this)->Span();
}

base::profidrive::E2::operator base::Fraction() const
{
	/* 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
	 * 放大后截断为整型。
	 *
	 * 想要获得分数的实际值，就将这个整型除以 Factor.
	 */

	int16_t value = _converter.ToInt16(Span());
	return value * base::Fraction{value, Factor()};
}

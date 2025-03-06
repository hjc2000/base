#include "N4.h"

int32_t base::profidrive::N4::Factor() const
{
	// 2 的 30 次方
	return static_cast<int64_t>(1 << 30);
}

base::profidrive::N4::N4(base::ReadOnlySpan const &value)
{
	Span().CopyFrom(value);
}

base::profidrive::N4::N4(base::Fraction const &value)
{
	/* 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
	 * 放大后截断为整型。
	 */
	int32_t result = static_cast<int32_t>(value * Factor());

	// 得到整型后要转换为大端序。
	_converter.GetBytes(result, Span());
}

base::Span base::profidrive::N4::Span()
{
	return _buffer.Span();
}

base::ReadOnlySpan base::profidrive::N4::Span() const
{
	return const_cast<N4 *>(this)->Span();
}

base::profidrive::N4::operator base::Fraction() const
{
	/* 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
	 * 放大后截断为整型。
	 *
	 * 想要获得分数的实际值，就将这个整型除以 Factor.
	 */

	int32_t value = _converter.ToInt32(Span());
	return value * base::Fraction{value, Factor()};
}

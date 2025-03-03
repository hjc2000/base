#include "C4.h"

int32_t base::C4::Factor() const
{
	return 10000;
}

base::C4::C4(base::ReadOnlySpan const &value)
{
	Span().CopyFrom(value);
}

base::C4::C4(base::Fraction const &value)
{
	/* 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
	 * 放大后截断为整型。
	 */
	int32_t result = static_cast<int32_t>(value * Factor());

	// 得到整型后要转换为大端序。
	_converter.GetBytes(result, Span());
}

base::Span base::C4::Span()
{
	return _buffer.AsArraySpan();
}

base::ReadOnlySpan base::C4::Span() const
{
	return const_cast<C4 *>(this)->Span();
}

base::C4::operator base::Fraction() const
{
	/* 行规特定数据类型用一个整型来储存它的值，这个整型值可以认为是将分数的实际值乘上 Factor
	 * 放大后截断为整型。
	 *
	 * 想要获得分数的实际值，就将这个整型除以 Factor.
	 */

	int32_t value = _converter.ToInt32(Span());
	return value * base::Fraction{value, Factor()};
}

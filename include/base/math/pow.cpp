#include "pow.h"

boost::multiprecision::cpp_int base::BigIntPow(boost::multiprecision::cpp_int x,
											   boost::multiprecision::cpp_int y)
{
	if (y < 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "y 不能 < 0."};
	}

	if (x == 0)
	{
		if (y == 0)
		{
			// 特殊情况，定义 0 ^ 0 = 1.
			return 1;
		}

		// 其他情况，0 的正整数次幂都为 0.
		return 0;
	}

	boost::multiprecision::cpp_int result = 1;
	for (int i = 0; i < y; i++)
	{
		result *= x;
	}

	return result;
}

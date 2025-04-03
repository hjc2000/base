#include "Pow.h"

boost::multiprecision::cpp_int base::BigIntPow(boost::multiprecision::cpp_int x,
											   boost::multiprecision::cpp_int y)
{
	if (x == 0)
	{
		return 0;
	}

	if (y < 0)
	{
		return 0;
	}

	boost::multiprecision::cpp_int result = 1;
	for (int i = 0; i < y; i++)
	{
		result *= x;
	}

	return result;
}

#include "Factorial.h"
#include <stdexcept>

base::BigInteger base::Factorial(base::BigInteger num)
{
	if (num < 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "负数没有定义阶乘。"};
	}

	if (num == 0)
	{
		return 1;
	}

	if (num == 1)
	{
		return 1;
	}

	return num * Factorial(num - 1);
}

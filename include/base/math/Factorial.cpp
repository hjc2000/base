#include "Factorial.h"
#include "base/string/define.h"
#include <stdexcept>

boost::multiprecision::cpp_int base::Factorial(boost::multiprecision::cpp_int num)
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

	boost::multiprecision::cpp_int result = 1;
	for (boost::multiprecision::cpp_int i = 1; i <= num; i++)
	{
		result *= i;
	}

	return result;
}

#include "BigInteger.h"

std::string base::BigInteger::ToString() const
{
	auto temp = _value;
	bool is_negative = temp < 0;
	std::string ret;
	if (temp < 0)
	{
		temp = -temp;
	}

	while (temp > 0)
	{
		uint8_t num = static_cast<uint8_t>(temp % 10);
		ret = std::to_string(num) + ret;
		temp /= 10;
	}

	if (is_negative)
	{
		ret = '-' + ret;
	}

	return ret;
}

#if HAS_THREAD
	#include <iostream>

void base::test::TestBigInteger()
{
	std::cout << CODE_POS_STR;
	base::BigInteger num{"-0x6666"};
	std::cout << num << std::endl;
}
#endif

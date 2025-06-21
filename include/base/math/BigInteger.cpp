#include "BigInteger.h"

std::string base::to_string(base::BigInteger const &value)
{
	base::BigInteger temp = value;
	bool is_negative = temp < 0;
	std::string ret;
	if (temp == 0)
	{
		return "0";
	}

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

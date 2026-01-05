#include "number_base.h"
#include <cmath>

std::vector<uint8_t> base::number_base::ConvertBase(uint64_t num, uint8_t base)
{
	std::vector<uint8_t> result;
	while (true)
	{
		uint64_t mod = num % base;
		result.push_back(mod);
		num /= base;
		if (num == 0)
		{
			break;
		}
	}

	return result;
}

uint64_t base::number_base::ToUInt64(std::vector<uint8_t> const &num, uint8_t base)
{
	uint64_t result = 0;
	for (uint64_t i = 0; i < num.size(); i++)
	{
		result += num[i] * std::pow(base, i);
	}

	return result;
}

std::vector<uint8_t> base::number_base::To8421BCD(uint64_t num)
{
	return ConvertBase(num, 10);
}

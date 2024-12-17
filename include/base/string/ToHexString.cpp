#include "ToHexString.h"
#include <stdexcept>

namespace
{
	/// @brief 将数字转化为 1 位 16 进制数字符。
	/// @param num 数字要在 1 位 16 进制数能表示的范围内，即：[0, 15].
	/// @return 表示 1 位 16 进制数的字符。
	char NumToOneHex(uint8_t num)
	{
		if (num > 15)
		{
			throw std::out_of_range{"数值超出范围"};
		}

		if (num < 10)
		{
			return '0' + num;
		}

		return 'a' + num - 10;
	}
} // namespace

std::string base::ToHexString(int8_t number, ToHexStringOption const &option)
{
	return ToHexString(static_cast<uint64_t>(number), option);
}

std::string base::ToHexString(uint8_t number, ToHexStringOption const &option)
{
	return ToHexString(static_cast<uint64_t>(number), option);
}

std::string base::ToHexString(int16_t number, ToHexStringOption const &option)
{
	return ToHexString(static_cast<uint64_t>(number), option);
}

std::string base::ToHexString(uint16_t number, ToHexStringOption const &option)
{
	return ToHexString(static_cast<uint64_t>(number), option);
}

std::string base::ToHexString(int32_t number, ToHexStringOption const &option)
{
	return ToHexString(static_cast<uint64_t>(number), option);
}

std::string base::ToHexString(uint32_t number, ToHexStringOption const &option)
{
	return ToHexString(static_cast<uint64_t>(number), option);
}

std::string base::ToHexString(int64_t number, ToHexStringOption const &option)
{
	return ToHexString(static_cast<uint64_t>(number), option);
}

std::string base::ToHexString(uint64_t number, ToHexStringOption const &option)
{
	std::string ret;
	while (true)
	{
		ret = NumToOneHex(number & 0xf) + ret;
		number >>= 4;
		if (number == 0)
		{
			break;
		}
	}

	while (static_cast<int32_t>(ret.size()) < option.width)
	{
		ret = '0' + ret;
	}

	if (option.with_0x_prefix)
	{
		ret = "0x" + ret;
	}

	return ret;
}

std::string base::ToHexString(void *p, ToHexStringOption const &option)
{
	return ToHexString(reinterpret_cast<uint64_t>(p), option);
}

std::string base::ToHexString(uint8_t *buffer,
							  int32_t size,
							  ToHexStringOption const &option)
{
	if (size <= 0)
	{
		return "";
	}

	std::string ret;
	for (int i = 0; i < size; i++)
	{
		ret += base::ToHexString(buffer[i], option) + ", ";
		if ((i + 1) % 16 == 0)
		{
			ret += '\n';
		}
	}

	ret += '\n';
	return ret;
}

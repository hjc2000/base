#include "ToHexString.h"
#include <algorithm>
#include <stdexcept>

namespace
{
	/**
	 * @brief 将数字转化为 1 位 16 进制数字符。
	 *
	 * @param num 数字要在 1 位 16 进制数能表示的范围内，即：[0, 15].
	 * @return char 表示 1 位 16 进制数的字符。
	 */
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

std::string base::ToHexString(int8_t number, ToHexStringOptions const &options)
{
	return ToHexString(static_cast<uint64_t>(number), options);
}

std::string base::ToHexString(uint8_t number, ToHexStringOptions const &options)
{
	return ToHexString(static_cast<uint64_t>(number), options);
}

std::string base::ToHexString(int16_t number, ToHexStringOptions const &options)
{
	return ToHexString(static_cast<uint64_t>(number), options);
}

std::string base::ToHexString(uint16_t number, ToHexStringOptions const &options)
{
	return ToHexString(static_cast<uint64_t>(number), options);
}

std::string base::ToHexString(int32_t number, ToHexStringOptions const &options)
{
	return ToHexString(static_cast<uint64_t>(number), options);
}

std::string base::ToHexString(uint32_t number, ToHexStringOptions const &options)
{
	return ToHexString(static_cast<uint64_t>(number), options);
}

std::string base::ToHexString(int64_t number, ToHexStringOptions const &options)
{
	return ToHexString(static_cast<uint64_t>(number), options);
}

std::string base::ToHexString(uint64_t number, ToHexStringOptions const &options)
{
	// 64 位数据，每 4 位需要一个 16 进制数来表示
	int reserve = 64 / 4;
	if (options.width > reserve)
	{
		// 填充后宽度大于实际内容，保留的空间定为 options.width.
		reserve = options.width;
	}

	if (options.with_0x_prefix)
	{
		// 还需要额外为 0x 前缀保留 2 个字节的空间。
		reserve += 2;
	}

	std::string ret;
	ret.reserve(reserve);

	// 倒着拼接，最后需要翻转
	while (true)
	{
		ret += NumToOneHex(number & 0xf);
		number >>= 4;
		if (number == 0)
		{
			break;
		}

		if (static_cast<int64_t>(ret.size()) > reserve)
		{
			throw std::runtime_error{"ToHexString 在拼接数字时结果特别长"};
		}
	}

	while (static_cast<int64_t>(ret.size()) < options.width)
	{
		ret += '0';
	}

	if (options.with_0x_prefix)
	{
		ret += "x0";
	}

	std::reverse(ret.begin(), ret.end());
	return ret;
}

std::string base::ToHexString(void const *p, ToHexStringOptions const &options)
{
	size_t address = reinterpret_cast<size_t>(p);
	return ToHexString(static_cast<uint64_t>(address), options);
}

std::string base::ToHexString(uint8_t const *buffer,
							  int64_t size,
							  ToHexStringOptions const &options)
{
	if (size <= 0)
	{
		return std::string{};
	}

	std::string ret{};

	/**
	 * 对于每个数字：
	 * 		@li 类似 0x00 这样的，占用 4 个字符。
	 * 		@li ", " 空白及逗号再占用 2 个字符。
	 */
	int reserve = (4 + 2) * size;

	// 每 16 个数字要有一个换行符，于是再加上 size/16
	reserve += size / 16;
	ret.reserve(reserve);

	for (int i = 0; i < size; i++)
	{
		if ((i % 16 == 0) && i > 0)
		{
			ret += '\n';
		}

		ret += base::ToHexString(buffer[i], options);
		if (i < size - 1)
		{
			ret += ", ";
		}
	}

	return ret;
}

std::string base::ToHexString(base::ReadOnlySpan const &span, ToHexStringOptions const &options)
{
	return ToHexString(span.Buffer(), span.Size(), options);
}

std::string base::ToHexString(base::Span const &span, ToHexStringOptions const &options)
{
	return ToHexString(base::ReadOnlySpan{span}, options);
}

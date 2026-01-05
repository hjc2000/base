#include "ToHexString.h"
#include "character.h"
#include <algorithm>
#include <stdexcept>

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
		ret += base::character::number_to_hex_char(number & 0xf, options.uppercase);
		number >>= 4;
		if (number == 0)
		{
			break;
		}

		if (static_cast<int64_t>(ret.size()) > reserve)
		{
			throw std::runtime_error{"ToHexString 在拼接数字时结果特别长。"};
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

std::u16string base::ToHexUtf16String(uint64_t number, ToHexStringOptions const &options)
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
		// 还需要额外为 0x 前缀保留 2 个字符的空间。
		reserve += 2;
	}

	std::u16string ret;
	ret.reserve(reserve);

	// 倒着拼接，最后需要翻转
	while (true)
	{
		ret += base::character::number_to_hex_utf16_char(number & 0xf);
		number >>= 4;
		if (number == 0)
		{
			break;
		}

		if (static_cast<int64_t>(ret.size()) > reserve)
		{
			throw std::runtime_error{"ToHexUtf16String 在拼接数字时结果特别长。"};
		}
	}

	while (static_cast<int64_t>(ret.size()) < options.width)
	{
		ret += u'0';
	}

	if (options.with_0x_prefix)
	{
		ret += u"x0";
	}

	std::reverse(ret.begin(), ret.end());
	return ret;
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

	// 对于每个数字：
	// 		类似 0x00 这样的，占用 4 个字符。
	// 		", " 空白及逗号再占用 2 个字符。
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

std::u16string base::ToHexUtf16String(uint8_t const *buffer,
									  int64_t size,
									  ToHexStringOptions const &options)
{
	if (size <= 0)
	{
		return std::u16string{};
	}

	std::u16string ret{};

	// 对于每个数字：
	// 		类似 0x00 这样的，占用 4 个字符。
	// 		", " 空白及逗号再占用 2 个字符。
	int reserve = (4 + 2) * size;

	// 每 16 个数字要有一个换行符，于是再加上 size/16
	reserve += size / 16;
	ret.reserve(reserve);

	for (int i = 0; i < size; i++)
	{
		if ((i % 16 == 0) && i > 0)
		{
			ret += u'\n';
		}

		ret += base::ToHexUtf16String(buffer[i], options);
		if (i < size - 1)
		{
			ret += u", ";
		}
	}

	return ret;
}

#include "Parse.h"
#include "base/container/Range.h"
#include "base/string/String.h"
#include <base/string/define.h>
#include <cstdint>
#include <stdexcept>

int32_t base::ParseInt32(base::String const &str)
{
	int32_t base = 10;
	base::String copy = str;
	copy.ToLower();
	if (copy.StartWith("0x"))
	{
		base = 16;
		copy = copy[base::Range{2, str.Length()}];
	}
	else if (copy.StartWith('0'))
	{
		base = 8;
		copy = copy[base::Range{1, str.Length()}];
	}

	return ParseInt32(copy.StdString(), base);
}

int32_t base::ParseInt32(base::String const &str, int32_t base)
{
	/**
	 * 解析时使用的子字符串的最后一个字符的下一个字符的索引。
	 * 如果整个字符串都用来被解析，则应该等于字符串长度。
	 */
	size_t parse_end_index = 0;
	int32_t result = std::stoi(str.StdString(), &parse_end_index, base);
	if (static_cast<int32_t>(parse_end_index) != str.Length())
	{
		// 没有将整个字符串都用来解析。
		throw std::invalid_argument("非法字符串。");
	}

	return result;
}

int64_t base::ParseInt64(base::String const &str)
{
	int32_t base = 10;
	base::String copy = str;
	copy.ToLower();
	if (copy.StartWith("0x"))
	{
		base = 16;
		copy = copy[base::Range{2, str.Length()}];
	}
	else if (copy.StartWith('0'))
	{
		base = 8;
		copy = copy[base::Range{1, str.Length()}];
	}

	return ParseInt64(copy.StdString(), base);
}

int64_t base::ParseInt64(base::String const &str, int32_t base)
{
	/**
	 * 解析时使用的子字符串的最后一个字符的下一个字符的索引。
	 * 如果整个字符串都用来被解析，则应该等于字符串长度。
	 */
	size_t parse_end_index = 0;
	int64_t result = std::stoll(str.StdString(), &parse_end_index, base);
	if (static_cast<int32_t>(parse_end_index) != str.Length())
	{
		// 没有将整个字符串都用来解析。
		throw std::invalid_argument("非法字符串。");
	}

	return result;
}

double base::ParseDouble(base::String const &str)
{
	/**
	 * 解析时使用的子字符串的最后一个字符的下一个字符的索引。
	 * 如果整个字符串都用来被解析，则应该等于字符串长度。
	 */
	size_t parse_end_index = 0;
	double result = std::stod(str.StdString(), &parse_end_index);
	if (static_cast<int32_t>(parse_end_index) != str.Length())
	{
		// 没有将整个字符串都用来解析。
		throw std::invalid_argument("非法字符串。");
	}

	return result;
}

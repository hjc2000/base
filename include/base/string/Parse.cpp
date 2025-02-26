#include "Parse.h"
#include "base/container/Range.h"
#include "base/string/define.h"
#include "base/string/String.h"
#include "base/string/StringSplitOptions.h"
#include <base/math/Fraction.h>
#include <base/math/Pow.h>
#include <base/string/define.h>
#include <cmath>
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
	else if (copy.StartWith('0') && copy.Length() > 1)
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
	else if (copy.StartWith('0') && copy.Length() > 1)
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
	int32_t base = 10;
	base::String copy = str;
	copy.ToLower();
	if (copy.StartWith("0x"))
	{
		base = 16;
		copy = copy[base::Range{2, str.Length()}];
	}
	else if (copy.StartWith('0') && copy.Length() > 1)
	{
		base = 8;
		copy = copy[base::Range{1, str.Length()}];
	}

	return ParseDouble(copy.StdString(), base);
}

double base::ParseDouble(base::String const &str, int32_t base)
{
	if (str.Length() == 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "不允许传入空字符串。"};
	}

	base::StringSplitOptions split_options{};
	split_options.remove_empty_substring = true;
	split_options.trim_each_substring = true;

	base::List<base::String> sub_strs = str.Split('.', split_options);
	if (sub_strs.Count() == 0 || sub_strs.Count() > 2)
	{
		throw std::invalid_argument{CODE_POS_STR + "非法字符串：" + str.StdString()};
	}

	base::String integer_part_str = sub_strs[0];
	base::String fractional_part_str = "0";
	if (sub_strs.Count() == 2)
	{
		fractional_part_str = sub_strs[1];
	}

	base::Fraction integer_part{base::ParseInt64(integer_part_str, base)};

	base::Fraction fractional_part{
		base::ParseInt64(fractional_part_str, base),
		base::IntPow(base, fractional_part_str.Length()),
	};

	base::Fraction sum = integer_part + fractional_part;
	return static_cast<double>(sum);
}

#include "Parse.h"
#include "base/container/Range.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include "base/string/String.h"
#include "base/string/StringSplitOptions.h"
#include <base/math/Fraction.h>
#include <base/math/Pow.h>
#include <base/string/define.h>
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <string>

namespace
{
	class BaseAndNumberStr
	{
	private:
		int32_t _base = 10;
		base::String _number_str = "0";

	public:
		BaseAndNumberStr(int32_t base, base::String const &number_str)
			: _base(base),
			  _number_str(number_str)
		{
		}

	public:
		int32_t Base() const
		{
			return _base;
		}

		base::String NumberString() const
		{
			return _number_str;
		}
	};

	BaseAndNumberStr ParseBase(base::String const &str)
	{
		int32_t base = 10;
		base::String number_str = str;
		number_str.ToLower();
		bool is_negative = false;

		{
			base::Span span = number_str.Span();
			if (span.StartWith('-'))
			{
				is_negative = true;
				span = span[base::Range{1, span.Size()}];
			}

			if (span.StartWith("0x"))
			{
				base = 16;
				span = span[base::Range{2, span.Size()}];
			}
			else if (span.StartWith('0') && span.Size() > 1)
			{
				base = 8;
				span = span[base::Range{1, span.Size()}];
			}

			if (span.StartWith('-'))
			{
				// 已经剥离了头部的 0x, 0 前缀了，此时如果出现负号，就是非法字符串。
				throw std::invalid_argument{CODE_POS_STR + "负号应该放到前缀前面。"};
			}

			number_str = base::String{span};
		}

		if (is_negative)
		{
			number_str = '-' + number_str;
		}

		return BaseAndNumberStr{base, number_str};
	}
} // namespace

int32_t base::ParseInt32(base::String const &str)
{
	auto info = ParseBase(str);
	return ParseInt32(info.NumberString(), info.Base());
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
		throw std::invalid_argument{CODE_POS_STR + "非法字符串：" + str.StdString()};
	}

	return result;
}

int64_t base::ParseInt64(base::String const &str)
{
	auto info = ParseBase(str);
	return ParseInt64(info.NumberString(), info.Base());
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
		throw std::invalid_argument{CODE_POS_STR + "非法字符串：" + str.StdString()};
	}

	return result;
}

double base::ParseDouble(base::String const &str)
{
	auto info = ParseBase(str);
	return ParseDouble(info.NumberString(), info.Base());
}

double base::ParseDouble(base::String const &str, int32_t base)
{
	if (str.Length() == 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "不允许传入空字符串。"};
	}

	base::String copy = str;
	bool is_negative = false;
	if (copy.StartWith('-'))
	{
		is_negative = true;
		copy = copy[base::Range{1, copy.Length()}];
	}

	base::StringSplitOptions split_options{};
	split_options.remove_empty_substring = true;
	split_options.trim_each_substring = true;

	base::List<base::String> sub_strs = copy.Split('.', split_options);
	if (sub_strs.Count() == 0 || sub_strs.Count() > 2)
	{
		throw std::invalid_argument{CODE_POS_STR + "非法字符串：" + copy.StdString()};
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
	if (is_negative)
	{
		sum = -sum;
	}

	return static_cast<double>(sum);
}

#if HAS_THREAD
	#include "base/string/define.h"
	#include <base/string/Parse.h>
	#include <iostream>
	#include <string>

void base::test::test_parse_int32()
{
	std::cout << "测试：" << CODE_POS_STR;

	std::string str{"10"};
	std::cout << "解析 10:\t" << base::ParseInt32(str) << std::endl;

	str = "0x10";
	std::cout << "解析 0x10:\t" << base::ParseInt32(str) << std::endl;

	str = "010";
	std::cout << "解析 010:\t" << base::ParseInt32(str) << std::endl;
}

void base::test::test_parse_int64()
{
	std::cout << "测试：" << CODE_POS_STR;

	std::string str{"-10"};
	std::cout << "解析 -10:\t" << base::ParseInt64(str) << std::endl;

	str = "-0x10";
	std::cout << "解析 -0x10:\t" << base::ParseInt64(str) << std::endl;

	str = "-010";
	std::cout << "解析 -010:\t" << base::ParseInt64(str) << std::endl;
}

void base::test::test_parse_double()
{
	std::cout << "测试：" << CODE_POS_STR;

	std::string str{"10"};
	std::cout << "解析 10:\t" << base::ParseDouble(str) << std::endl;

	str = "0x10";
	std::cout << "解析 0x10:\t" << base::ParseDouble(str) << std::endl;

	str = "010";
	std::cout << "解析 010:\t" << base::ParseDouble(str) << std::endl;

	str = "-0x10.5";
	std::cout << "解析 -0x10.5:\t" << base::ParseDouble(str) << std::endl;

	str = "10.5";
	std::cout << "解析 16 进制 10.5:\t" << base::ParseDouble(str, 16) << std::endl;
	std::cout << "解析 8 进制 10.5:\t" << base::ParseDouble(str, 8) << std::endl;
}

#endif

#include "Parse.h"
#include <base/string/define.h>

int32_t base::ParseInt32(std::string const &str, base::ParseOptions const &options)
{
	/**
	 * 解析时使用的子字符串的最后一个字符的下一个字符的索引。
	 * 如果整个字符串都用来被解析，则应该等于字符串长度。
	 */
	size_t parse_end_index = 0;
	int32_t result = std::stoi(str, &parse_end_index, options._base);
	if (parse_end_index != str.size())
	{
		// 没有将整个字符串都用来解析。
		throw std::invalid_argument("非法字符串。");
	}

	return result;
}

int64_t base::ParseInt64(std::string const &str, base::ParseOptions const &options)
{
	/**
	 * 解析时使用的子字符串的最后一个字符的下一个字符的索引。
	 * 如果整个字符串都用来被解析，则应该等于字符串长度。
	 */
	size_t parse_end_index = 0;
	int64_t result = std::stoll(str, &parse_end_index, options._base);
	if (parse_end_index != str.size())
	{
		// 没有将整个字符串都用来解析。
		throw std::invalid_argument("非法字符串。");
	}

	return result;
}

double base::ParseDouble(std::string const &str, base::ParseOptions const &options)
{
	if (options._base != 10)
	{
		throw std::invalid_argument{CODE_POS_STR + "浮点数不支持非 10 进制。"};
	}

	/**
	 * 解析时使用的子字符串的最后一个字符的下一个字符的索引。
	 * 如果整个字符串都用来被解析，则应该等于字符串长度。
	 */
	size_t parse_end_index = 0;
	double result = std::stod(str, &parse_end_index);
	if (parse_end_index != str.size())
	{
		// 没有将整个字符串都用来解析。
		throw std::invalid_argument("非法字符串。");
	}

	return result;
}

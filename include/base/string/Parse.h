#pragma once
#include <base/string/String.h>
#include <stdint.h>

namespace base
{
	///
	/// @brief 从字符串中解析 int32_t.
	///
	/// @param str 可以是十进制数字符串，0x 开头的 16 进制数字符串，0 开头的 8 进制数字符串。
	/// @return int32_t
	///
	int32_t ParseInt32(base::String const &str);

	///
	/// @brief 从字符串中解析 int32_t.
	///
	/// @param str 可以是 10 进制，16 进制，8 进制数的字符串，但是不能有 0x 之类的前缀。
	/// @param base 指定字符串中数字的进制数。
	///
	/// @return int32_t
	///
	int32_t ParseInt32(base::String const &str, int32_t base);

	///
	/// @brief 从字符串中解析 int64_t.
	///
	/// @param str 可以是十进制数字符串，0x 开头的 16 进制数字符串，0 开头的 8 进制数字符串。
	/// @return int64_t
	///
	int64_t ParseInt64(base::String const &str);

	///
	/// @brief 从字符串中解析 int64_t.
	///
	/// @param str 可以是 10 进制，16 进制，8 进制数的字符串，但是不能有 0x 之类的前缀。
	/// @param base 指定字符串中数字的进制数。
	///
	/// @return int64_t
	///
	int64_t ParseInt64(base::String const &str, int32_t base);

	///
	/// @brief 从字符串中解析 double.
	///
	/// @param str 可以是十进制数字符串，0x 开头的 16 进制数字符串，0 开头的 8 进制数字符串。
	/// @return double
	///
	double ParseDouble(base::String const &str);

	///
	/// @brief 从字符串中解析 double
	///
	/// @param str 可以是 10 进制，16 进制，8 进制数的字符串，但是不能有 0x 之类的前缀。
	/// @param base 指定字符串中数字的进制数。
	///
	/// @return double
	///
	double ParseDouble(base::String const &str, int32_t base);

#if HAS_THREAD
	namespace test
	{
		void test_parse_int32();

		void test_parse_int64();

		void test_parse_double();
	} // namespace test
#endif
} // namespace base

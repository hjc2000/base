#pragma once
#include "base/string/String.h"
#include <cstdint>

namespace base
{
	///
	/// @brief 从字符串中解析 int32_t.
	///
	/// @param str 可以是十进制数字符串，0x 开头的 16 进制数字符串，0 开头的 8 进制数字符串。
	///
	/// @return
	///
	int32_t ParseInt32(base::String const &str);

	///
	/// @brief 从字符串中解析 int32_t.
	///
	/// @param str 可以是 10 进制，16 进制，8 进制数的字符串，但是不能有 0x 之类的前缀。
	/// @param base 指定字符串中数字的进制数。
	///
	/// @return
	///
	int32_t ParseInt32(base::String const &str, int32_t base);

	///
	/// @brief 从字符串中解析 int64_t.
	///
	/// @param str 可以是十进制数字符串，0x 开头的 16 进制数字符串，0 开头的 8 进制数字符串。
	///
	/// @return
	///
	int64_t ParseInt64(base::String const &str);

	///
	/// @brief 从字符串中解析 int64_t.
	///
	/// @param str 可以是 10 进制，16 进制，8 进制数的字符串，但是不能有 0x 之类的前缀。
	/// @param base 指定字符串中数字的进制数。
	///
	/// @return
	///
	int64_t ParseInt64(base::String const &str, int32_t base);

	///
	/// @brief 从字符串中解析 double.
	///
	/// @param str 可以是十进制数字符串，0x 开头的 16 进制数字符串，0 开头的 8 进制数字符串。
	///
	/// @return
	///
	double ParseDouble(base::String const &str);

	///
	/// @brief 从字符串中解析 double
	///
	/// @param str 可以是 10 进制，16 进制，8 进制数的字符串，但是不能有 0x 之类的前缀。
	/// @param base 指定字符串中数字的进制数。
	///
	/// @return
	///
	double ParseDouble(base::String const &str, int32_t base);

} // namespace base

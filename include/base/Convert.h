#pragma once
#include <cstdlib>
#include <stdexcept>
#include <stdint.h>
#include <string>

namespace base
{
	/// @brief 统一定义转换函数的样子。要实现转换逻辑时就特化一个本函数。
	/// @tparam ReturnType
	/// @tparam InputType
	/// @param o
	/// @return
	template <typename ReturnType, typename InputType>
	inline ReturnType Convert(InputType const &o) = delete;

	template <>
	inline int32_t Convert<int32_t, std::string>(std::string const &o)
	{
		return std::stoi(o.c_str());
	}

	// 显式特化：从 std::string 转换到 int64_t
	template <>
	inline int64_t Convert<int64_t, std::string>(std::string const &o)
	{
		/**
		 * 解析后，会将此指针指向解析时所用的最后一个字符的下一个字符。如果整个字符串都用来被解析了，
		 * 则会指向 \0 字符。
		 */
		char *end{};

		// 假设字符串中的数是 10 进制数。
		int64_t result = std::strtoll(o.c_str(), &end, 10);
		if (*end != '\0')
		{
			// 检查是否成功解析整个字符串
			throw std::invalid_argument("非法字符串。");
		}

		return result;
	}
} // namespace base

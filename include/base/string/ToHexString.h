#pragma once
#include <base/stream/ReadOnlySpan.h>
#include <stdint.h>
#include <string>

namespace base
{
	/// @brief ToHexString 函数的选项。
	struct ToHexStringOption
	{
		/// @brief 是否有 0x 前缀
		bool with_0x_prefix = true;

		/// @brief 是否需要让输出的字符串固定位宽，不够位宽就在左侧填充 0.如果需要的话，
		/// 将本字段赋值为大于 0 的值。
		int width = -1;
	};

	/// @brief 将数字转化为 16 进制的字符串
	/// @param number
	/// @param option
	/// @return
	std::string ToHexString(int8_t number, ToHexStringOption const &option = ToHexStringOption{});

	/// @brief 将数字转化为 16 进制的字符串
	/// @param number
	/// @param option
	/// @return
	std::string ToHexString(uint8_t number, ToHexStringOption const &option = ToHexStringOption{});

	/// @brief 将数字转化为 16 进制的字符串
	/// @param number
	/// @param option
	/// @return
	std::string ToHexString(int16_t number, ToHexStringOption const &option = ToHexStringOption{});

	/// @brief 将数字转化为 16 进制的字符串
	/// @param number
	/// @param option
	/// @return
	std::string ToHexString(uint16_t number, ToHexStringOption const &option = ToHexStringOption{});

	/// @brief 将数字转化为 16 进制的字符串
	/// @param number
	/// @param option
	/// @return
	std::string ToHexString(int32_t number, ToHexStringOption const &option = ToHexStringOption{});

	/// @brief 将数字转化为 16 进制的字符串
	/// @param number
	/// @param option
	/// @return
	std::string ToHexString(uint32_t number, ToHexStringOption const &option = ToHexStringOption{});

	/// @brief 将数字转化为 16 进制的字符串
	/// @param number
	/// @param option
	/// @return
	std::string ToHexString(int64_t number, ToHexStringOption const &option = ToHexStringOption{});

	/// @brief 将数字转化为 16 进制的字符串
	/// @param number
	/// @param option
	/// @return
	std::string ToHexString(uint64_t number, ToHexStringOption const &option = ToHexStringOption{});

	/// @brief 将指针转化为 16 进制数。
	/// @param p
	/// @param option
	/// @return
	std::string ToHexString(void const *p, ToHexStringOption const &option = ToHexStringOption{});

	/// @brief 将缓冲区中的每个字节变成 16 进制字符串，每个字节的字符串用逗号分隔，每
	/// 20 个字节一行。
	/// @param buffer
	/// @param size
	/// @return
	std::string ToHexString(uint8_t const *buffer,
							int32_t size,
							ToHexStringOption const &option = ToHexStringOption{});

	std::string ToHexString(base::ReadOnlySpan const &span,
							ToHexStringOption const &option = ToHexStringOption{});

	std::string ToHexString(base::Span const &span,
							ToHexStringOption const &option = ToHexStringOption{});
} // namespace base

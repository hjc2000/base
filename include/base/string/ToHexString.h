#pragma once
#include "base/stream/ReadOnlySpan.h"
#include <cstdint>
#include <string>

namespace base
{
	///
	/// @brief ToHexString 函数的选项。
	///
	///
	struct ToHexStringOptions
	{
		///
		/// @brief 是否有 0x 前缀
		///
		///
		bool with_0x_prefix = true;

		///
		/// @brief 是否需要让输出的字符串固定位宽，不够位宽就在左侧填充 0.如果需要的话，
		/// 将本字段赋值为大于 0 的值。
		///
		int width = -1;
	};

	///
	/// @brief 将数字转化为 16 进制的字符串。
	///
	/// @param number
	/// @param options
	///
	/// @return
	///
	std::string ToHexString(int8_t number, ToHexStringOptions const &options = ToHexStringOptions{});

	///
	/// @brief 将数字转化为 16 进制的字符串。
	///
	/// @param number
	/// @param options
	///
	/// @return
	///
	std::string ToHexString(uint8_t number, ToHexStringOptions const &options = ToHexStringOptions{});

	///
	/// @brief 将数字转化为 16 进制的字符串。
	///
	/// @param number
	/// @param options
	///
	/// @return
	///
	std::string ToHexString(int16_t number, ToHexStringOptions const &options = ToHexStringOptions{});

	///
	/// @brief 将数字转化为 16 进制的字符串。
	///
	/// @param number
	/// @param options
	///
	/// @return
	///
	std::string ToHexString(uint16_t number, ToHexStringOptions const &options = ToHexStringOptions{});

	///
	/// @brief 将数字转化为 16 进制的字符串。
	///
	/// @param number
	/// @param options
	///
	/// @return
	///
	std::string ToHexString(int32_t number, ToHexStringOptions const &options = ToHexStringOptions{});

	///
	/// @brief 将数字转化为 16 进制的字符串。
	///
	/// @param number
	/// @param options
	///
	/// @return
	///
	std::string ToHexString(uint32_t number, ToHexStringOptions const &options = ToHexStringOptions{});

	///
	/// @brief 将数字转化为 16 进制的字符串。
	///
	/// @param number
	/// @param options
	///
	/// @return
	///
	std::string ToHexString(int64_t number, ToHexStringOptions const &options = ToHexStringOptions{});

	///
	/// @brief 将数字转化为 16 进制的字符串。
	///
	/// @param number
	/// @param options
	///
	/// @return
	///
	std::string ToHexString(uint64_t number, ToHexStringOptions const &options = ToHexStringOptions{});

	///
	/// @brief 将指针转换为 16 进制字符串。
	///
	/// @param p
	/// @param options
	///
	/// @return
	///
	std::string ToHexString(void const *p, ToHexStringOptions const &options = ToHexStringOptions{});

	///
	/// @brief 将缓冲区中的每个字节变成 16 进制字符串，每个字节的字符串用逗号分隔，
	/// 每 16 个字节一行。
	///
	/// @param buffer
	/// @param size
	/// @param options
	/// @return
	///
	std::string ToHexString(uint8_t const *buffer,
							int32_t size,
							ToHexStringOptions const &options = ToHexStringOptions{});

	///
	/// @brief 将缓冲区中的每个字节变成 16 进制字符串，每个字节的字符串用逗号分隔，
	/// 每 16 个字节一行。
	///
	/// @param span
	/// @param options
	/// @return
	///
	std::string ToHexString(base::ReadOnlySpan const &span,
							ToHexStringOptions const &options = ToHexStringOptions{});

	///
	/// @brief 将缓冲区中的每个字节变成 16 进制字符串，每个字节的字符串用逗号分隔，
	/// 每 16 个字节一行。
	///
	/// @param span
	/// @param options
	/// @return
	///
	std::string ToHexString(base::Span const &span,
							ToHexStringOptions const &options = ToHexStringOptions{});
} // namespace base

#pragma once
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include <cstdint>
#include <string>
#include <type_traits>

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

		///
		/// @brief 转换成的 16 进制数字符串是否使用大写字母。
		///
		bool uppercase = false;
	};

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
	/// @brief 将数字转化为 16 进制的字符串。
	///
	/// @param number
	/// @param options
	/// @return
	///
	std::u16string ToHexUtf16String(uint64_t number, ToHexStringOptions const &options = ToHexStringOptions{});

	///
	/// @brief 将数字转化为 16 进制的字符串。
	///
	/// @param number
	/// @param options
	///
	/// @return
	///
	template <typename T>
		requires(std::is_integral_v<T> && !std::is_same_v<T, uint64_t>)
	std::string ToHexString(T number, ToHexStringOptions const &options = ToHexStringOptions{})
	{
		return ToHexString(static_cast<uint64_t>(number), options);
	}

	///
	/// @brief 将数字转化为 16 进制的字符串。
	///
	/// @param number
	/// @param options
	///
	/// @return
	///
	template <typename T>
		requires(std::is_integral_v<T> && !std::is_same_v<T, uint64_t>)
	std::u16string ToHexUtf16String(T number, ToHexStringOptions const &options = ToHexStringOptions{})
	{
		return ToHexUtf16String(static_cast<uint64_t>(number), options);
	}

	///
	/// @brief 将指针转换为 16 进制字符串。
	///
	/// @param p
	/// @param options
	///
	/// @return
	///
	inline std::string ToHexString(void const *p, ToHexStringOptions const &options = ToHexStringOptions{})
	{
		size_t address = reinterpret_cast<size_t>(p);
		return ToHexString(static_cast<uint64_t>(address), options);
	}

	///
	/// @brief 将指针转换为 16 进制字符串。
	///
	/// @param p
	/// @param options
	///
	/// @return
	///
	inline std::u16string ToHexUtf16String(void const *p, ToHexStringOptions const &options = ToHexStringOptions{})
	{
		size_t address = reinterpret_cast<size_t>(p);
		return ToHexUtf16String(static_cast<uint64_t>(address), options);
	}

	///
	/// @brief 将缓冲区中的每个字节变成 16 进制字符串，每个字节的字符串用逗号分隔，
	/// 每 16 个字节一行。
	///
	/// @param buffer
	/// @param size
	/// @param options
	///
	/// @return
	///
	std::string ToHexString(uint8_t const *buffer,
							int64_t size,
							ToHexStringOptions const &options = ToHexStringOptions{});

	/// @brief 将缓冲区中的每个字节变成 16 进制字符串，每个字节的字符串用逗号分隔，
	/// 每 16 个字节一行。
	///
	/// @param buffer
	/// @param size
	/// @param options
	///
	/// @return
	///
	std::u16string ToHexUtf16String(uint8_t const *buffer,
									int64_t size,
									ToHexStringOptions const &options = ToHexStringOptions{});

	///
	/// @brief 将缓冲区中的每个字节变成 16 进制字符串，每个字节的字符串用逗号分隔，
	/// 每 16 个字节一行。
	///
	/// @param span
	/// @param options
	///
	/// @return
	///
	inline std::string ToHexString(base::ReadOnlySpan const &span,
								   ToHexStringOptions const &options = ToHexStringOptions{})
	{
		return ToHexString(span.Buffer(), span.Size(), options);
	}

	///
	/// @brief 将缓冲区中的每个字节变成 16 进制字符串，每个字节的字符串用逗号分隔，
	/// 每 16 个字节一行。
	///
	/// @param span
	/// @param options
	///
	/// @return
	///
	inline std::u16string ToHexUtf16String(base::ReadOnlySpan const &span,
										   ToHexStringOptions const &options = ToHexStringOptions{})
	{
		return ToHexUtf16String(span.Buffer(), span.Size(), options);
	}

	///
	/// @brief 将缓冲区中的每个字节变成 16 进制字符串，每个字节的字符串用逗号分隔，
	/// 每 16 个字节一行。
	///
	/// @param span
	/// @param options
	///
	/// @return
	///
	inline std::string ToHexString(base::Span const &span,
								   ToHexStringOptions const &options = ToHexStringOptions{})
	{
		return ToHexString(base::ReadOnlySpan{span}, options);
	}

	///
	/// @brief 将缓冲区中的每个字节变成 16 进制字符串，每个字节的字符串用逗号分隔，
	/// 每 16 个字节一行。
	///
	/// @param span
	/// @param options
	///
	/// @return
	///
	inline std::u16string ToHexUtf16String(base::Span const &span,
										   ToHexStringOptions const &options = ToHexStringOptions{})
	{
		return ToHexUtf16String(base::ReadOnlySpan{span}, options);
	}

} // namespace base

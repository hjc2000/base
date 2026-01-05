#pragma once
#include "base/stream/ReadOnlySpan.h"
#include <algorithm>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <string>

namespace base::string::encoding
{
	///
	/// @brief 让传入的 str 的内部缓冲区中的数据变成 UTF16-LE 字节序列。
	///
	/// @note 如果本机是小端序，不需要任何处理，std::u16string 中的数据本来就是
	/// UTF16-LE 字节序列。
	///
	/// @note 如果本机是大端序，需要转换，则直接颠倒每个字符的字节序，
	/// 让缓冲区中的数据变成 UTF16-LE 字节序列。
	///
	/// @warning 如果发生了转换，经过处理后的 str 中的字符的值将不再正确，只能够
	/// 读取其中的缓冲区进行发送，不能够进行字符处理。
	///
	/// @param str
	///
	inline void convert_to_utf16le_string(std::u16string &str)
	{
		if (std::endian::native == std::endian::little)
		{
			return;
		}

		// 本机不是小端序，需要转换。
		for (size_t i = 0; i < str.size(); i++)
		{
			std::reverse(reinterpret_cast<uint8_t *>(&str[i]),
						 reinterpret_cast<uint8_t *>(&str[i]) + sizeof(char16_t));
		}
	}

	///
	/// @brief 将传入的 span 中的 ASCII 字符串转换成 UTF16 字符串。
	///
	/// @param span
	/// @return
	///
	inline std::u16string convert_ascii_to_utf16_string(base::ReadOnlySpan const &span)
	{
		std::u16string ret;
		ret.reserve(span.Size());

		for (int64_t i = 0; i < span.Size(); i++)
		{
			ret.push_back(static_cast<char16_t>(span[i]));
		}

		return ret;
	}

} // namespace base::string::encoding

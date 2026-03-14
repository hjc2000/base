#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/bit/bit.h"
#include "base/container/ReadOnlyArraySpan.h"
#include "base/stream/Stream.h"
#include "base/string/define.h"
#include <cstdint>
#include <stdexcept>
#include <string>

namespace base::string::encoding
{
	class Utf16LeWriter
	{
	private:
		base::Stream &_stream;

	public:
		Utf16LeWriter(base::Stream &stream)
			: _stream{stream}
		{
		}

		///
		/// @brief 写入单个字符。
		///
		/// @note 将会转换为 UTF16LE 然后写入流中。
		///
		/// @param value
		///
		void Write(char32_t value)
		{
			if (value >= 0xd800 && value <= 0xdfff)
			{
				// 非法码点，替换为错误字符 0xfffd.
				uint16_t c = 0xfffd;
				base::little_endian_remote_converter.GetBytes(c, _stream);
				return;
			}

			if (value < 0x10000)
			{
				// 剔除掉非法码点后，小于 0x10000 的码点可以直接赋值。
				uint16_t c = static_cast<uint16_t>(value);
				base::little_endian_remote_converter.GetBytes(c, _stream);
				return;
			}

			if (value >= 0x10000 && value <= 0x10FFFF)
			{
				char32_t c = value - 0x10000;
				uint16_t low = base::bit::ReadBits(c, 0, 10);
				uint16_t high = base::bit::ReadBits(c, 10, 20);

				high += 0xd800;
				low += 0xdc00;

				base::little_endian_remote_converter.GetBytes(high, _stream);
				base::little_endian_remote_converter.GetBytes(low, _stream);
			}

			throw std::invalid_argument{CODE_POS_STR + "非法码点。"};
		}

		///
		/// @brief 将字符串用 UTF16LE 编码后写入流中。
		///
		/// @param span
		///
		void Write(base::ReadOnlyArraySpan<char32_t> const &span)
		{
			for (int64_t i = 0; i < span.Count(); i++)
			{
				Write(span[i]);
			}
		}

		///
		/// @brief 将字符串用 UTF16LE 编码后写入流中。
		///
		/// @param str
		///
		void Write(std::u32string const &str)
		{
			base::ReadOnlyArraySpan<char32_t> span{
				str.data(),
				static_cast<int64_t>(str.size()),
			};

			Write(span);
		}

		///
		/// @brief 将字符串用 UTF16LE 编码后写入流中。
		///
		/// @param str
		///
		void Write(char32_t const *str)
		{
			int64_t length = 0;

			while (str[length] != 0)
			{
				length++;
			}

			base::ReadOnlyArraySpan<char32_t> span{
				str,
				length,
			};

			Write(span);
		}
	};

} // namespace base::string::encoding

#pragma once
#include "base/bit/bit.h"
#include "base/container/ArraySpan.h"
#include "base/container/CircleDeque.h"
#include "base/math/math.h"
#include "base/stream/Stream.h"
#include <cstdint>

namespace base::string::encoding
{
	class Utf8Reader
	{
	private:
		base::Stream &_stream;
		base::CircleDeque<uint8_t, 16> _queue;

		///
		/// @brief 每次 Read 函数调用会重置。相当于临时变量，只不过为了能在各个方法之间
		/// 共享，同时避免繁琐的函数调用传参才安排成上下文类。
		///
		struct reading_context
		{
			base::ArraySpan<char32_t> _span;

			int64_t _total_read = 0;
		};

		reading_context _reading_context;

		///
		/// @brief UTF8 解析遇到非法序列时，每个非法序列将被替换为 1 个该字符。
		///
		/// @return
		///
		static constexpr char32_t ReplacementCharacter()
		{
			return static_cast<char32_t>(0xfffd);
		}

		///
		/// @brief 尝试从流中读取字节，将队列填充到半满。
		///
		/// @note 如果调用后队列仍然为空，说明流到尽头了。
		///
		void FillHalfQueue();

		///
		/// @brief 判断一个字节是不是 UTF-8 序列的开头。
		///
		/// @param byte
		/// @return
		///
		bool IsValidUtf8SequenceStart(uint8_t byte);

		///
		/// @brief 判断一个字节是不是 UTF-8 序列继首字节之后的继续字节。
		///
		/// @param byte
		/// @return
		///
		bool IsValidUtf8ContinueByte(uint8_t byte)
		{
			int high_one_count = base::bit::HighOneCount(byte);
			return high_one_count == 1;
		}

		/* #region 码点范围检查 */

		static constexpr bool IsValidOneByteUnicodeCharacter(char32_t value)
		{
			if (value >= base::pow<char32_t>(2, 7))
			{
				return false;
			}

			return true;
		}

		static constexpr bool IsValidTwoByteUnicodeCharacter(char32_t value)
		{
			if (value < base::pow<char32_t>(2, 7))
			{
				return false;
			}

			if (value >= base::pow<char32_t>(2, 11))
			{
				return false;
			}

			return true;
		}

		static constexpr bool IsValidThreeByteUnicodeCharacter(char32_t value)
		{
			if (value < base::pow<char32_t>(2, 11))
			{
				return false;
			}

			if (value >= base::pow<char32_t>(2, 16))
			{
				return false;
			}

			// 排除 UTF-16 代理区：U+D800 到 U+DFFF
			if (value >= 0xD800 && value <= 0xDFFF)
			{
				return false;
			}

			return true;
		}

		static constexpr bool IsValidFourByteUnicodeCharacter(char32_t value)
		{
			if (value < base::pow<char32_t>(2, 16))
			{
				return false;
			}

			// 注意：这里是 >，因为 0x10FFFF 是合法的。
			if (value > 0x10FFFF)
			{
				return false;
			}

			return true;
		}

		/* #endregion */

		///
		/// @brief 定位到下一个 UTF-8 序列的开头。
		///
		/// @note 调用后，队列中的第 1 个字节将会是 UTF-8 序列的开头。
		///
		/// @note 或者队列空了，流也结束了，还是无法定位到 UTF-8 序列开头，
		/// 这种情况下调用本函数后，队列将为空。
		///
		void SeekToNextSequence();

		void DecodeOneByteCaracter(uint8_t byte1);
		void DecodeTwoByteCaracter(uint8_t byte1);
		void DecodeThreeByteCaracter(uint8_t byte1);
		void DecodeFourByteCaracter(uint8_t byte1);
		void DecodeOneCharacter();

	public:
		Utf8Reader(base::Stream &stream)
			: _stream(stream)
		{
		}

		///
		/// @brief 从流中读取字节，解码位 UTF-32 字符，放入 span 中。
		///
		/// @param span
		///
		/// @return 成功解码出的字符数。
		/// 	@note 返回 0 表示流已结束。
		///
		int64_t Read(base::ArraySpan<char32_t> const &span);
	};

} // namespace base::string::encoding

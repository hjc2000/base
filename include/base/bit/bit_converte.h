#pragma once
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/stream/Stream.h"
#include "base/string/define.h"
#include <algorithm>
#include <stdexcept>

namespace base
{
	namespace bit_converte
	{
		/* #region 转换为数值类型 */

		///
		/// @brief 从 span 中反序列化出 uint16_t.
		///
		/// @param span
		/// @return uint16_t
		///
		uint16_t ToUInt16(base::ReadOnlySpan const &span);

		///
		/// @brief 从 stream 中反序列化出 uint16_t.
		///
		/// @param stream
		/// @return uint16_t
		///
		uint16_t ToUInt16(base::Stream &stream);

		///
		/// @brief 从 span 中反序列化出 int16_t.
		///
		/// @param span
		/// @return int16_t
		///
		int16_t ToInt16(base::ReadOnlySpan const &span);

		///
		/// @brief 从 stream 中反序列化出 int16_t.
		///
		/// @param stream
		/// @return int16_t
		///
		int16_t ToInt16(base::Stream &stream);

		///
		/// @brief 将高字节和低字节拼接成 uint16_t.
		///
		/// @param high
		/// @param low
		/// @return uint16_t
		///
		uint16_t ToUInt16(uint8_t high, uint8_t low);

		///
		/// @brief 从 span 中反序列化出 uint32_t.
		///
		/// @param span
		/// @return uint32_t
		///
		uint32_t ToUInt32(base::ReadOnlySpan const &span);

		///
		/// @brief 从 stream 中反序列化出 uint32_t.
		///
		/// @param stream
		/// @return uint32_t
		///
		uint32_t ToUInt32(base::Stream &stream);

		///
		/// @brief 从 span 中反序列化出 int32_t.
		///
		/// @param span
		/// @return int32_t
		///
		int32_t ToInt32(base::ReadOnlySpan const &span);

		///
		/// @brief 从 stream 中反序列化出 int32_t.
		///
		/// @param stream
		/// @return int32_t
		///
		int32_t ToInt32(base::Stream &stream);

		///
		/// @brief 将 4 个字节拼接成 uint32_t. b0 是最低字节，b3 是最高字节。
		///
		/// @param b3 最高字节
		/// @param b2
		/// @param b1
		/// @param b0 最低字节
		/// @return uint32_t
		///
		uint32_t ToUInt32(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0);

		///
		/// @brief 将低 uint16_t 和高 uint16_t 拼接成 uint32_t.
		///
		/// @param high
		/// @param low
		/// @return uint32_t
		///
		uint32_t ToUInt32(uint16_t high, uint16_t low);

		///
		/// @brief 从 span 中反序列化出 uint64_t.
		///
		/// @param span
		/// @return uint64_t
		///
		uint64_t ToUInt64(base::ReadOnlySpan const &span);

		///
		/// @brief 从 stream 中反序列化出 uint64_t.
		///
		/// @param stream
		/// @return uint64_t
		///
		uint64_t ToUInt64(base::Stream &stream);

		///
		/// @brief 从 span 中反序列化出 int64_t.
		///
		/// @param span
		/// @return int64_t
		///
		int64_t ToInt64(base::ReadOnlySpan const &span);

		///
		/// @brief 从 stream 中反序列化出 int64_t.
		///
		/// @param stream
		/// @return int64_t
		///
		int64_t ToInt64(base::Stream &stream);

		///
		/// @brief 从 span 中反序列化出 float.
		///
		/// @param span
		/// @return float
		///
		float ToFloat(base::ReadOnlySpan const &span);

		///
		/// @brief 从 stream 中反序列化出 float.
		///
		/// @param stream
		/// @return float
		///
		float ToFloat(base::Stream &stream);

		///
		/// @brief 从 span 中反序列化出 double.
		///
		/// @param span
		/// @return double
		///
		double ToDouble(base::ReadOnlySpan const &span);

		///
		/// @brief 从 stream 中反序列化出 double.
		///
		/// @param stream
		/// @return double
		///
		double ToDouble(base::Stream &stream);

		/* #endregion */

		/* #region FromBytes */

		///
		/// @brief 从字节序列中反序列化出 ReturnType.
		///
		/// @param span
		/// @return ReturnType
		///
		template <typename ReturnType>
		ReturnType FromBytes(base::ReadOnlySpan const &span)
		{
			if (span.Size() < static_cast<int32_t>(sizeof(ReturnType)))
			{
				throw std::invalid_argument{CODE_POS_STR + "传入的 span 太小。"};
			}

			ReturnType ret{};

			std::copy(span.Buffer(),
					  span.Buffer() + sizeof(ret),
					  reinterpret_cast<uint8_t *>(&ret));

			return ret;
		}

		///
		/// @brief 从流中反序列化出 ReturnType.
		///
		/// @param stream
		/// @return ReturnType
		///
		template <typename ReturnType>
		ReturnType FromBytes(base::Stream &stream)
		{
			uint8_t buffer[sizeof(ReturnType)];

			base::Span span{
				buffer,
				static_cast<int32_t>(sizeof(ReturnType)),
			};

			int32_t have_read = stream.ReadExactly(span);
			if (have_read < span.Size())
			{
				throw std::runtime_error{CODE_POS_STR + "流中没有足够的字节。"};
			}

			return FromBytes<ReturnType>(span);
		}

		/* #endregion */

		/* #region GetBytes */

		///
		/// @brief 将 value 序列化，写入 span 中。
		///
		/// @param value
		/// @param span
		///
		template <typename ValueType>
		void GetBytes(ValueType value, base::Span const &span)
		{
			if (span.Size() < static_cast<int32_t>(sizeof(ValueType)))
			{
				throw std::invalid_argument{CODE_POS_STR + "传入的 span 太小。"};
			}

			uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);

			std::copy(buffer,
					  buffer + sizeof(ValueType),
					  span.Buffer());
		}

		///
		/// @brief 将 value 序列化，写入 stream 中。
		///
		/// @param value
		/// @param stream
		///
		template <typename ValueType>
		void GetBytes(ValueType value, base::Stream &stream)
		{
			uint8_t *buffer = reinterpret_cast<uint8_t *>(&value);
			stream.Write(buffer, 0, sizeof(value));
		}

		/* #endregion */

	} // namespace bit_converte
} // namespace base

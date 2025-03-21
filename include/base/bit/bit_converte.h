#pragma once
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Stream.h"

namespace base
{
	namespace bit_converte
	{
		/**
		 * @brief 从 span 中反序列化出 uint16_t.
		 *
		 * @param span
		 * @return uint16_t
		 */
		uint16_t ToUInt16(base::ReadOnlySpan const &span);

		/**
		 * @brief 从 stream 中反序列化出 uint16_t.
		 *
		 * @param stream
		 * @return uint16_t
		 */
		uint16_t ToUInt16(base::Stream &stream);

		/**
		 * @brief 从 span 中反序列化出 int16_t.
		 *
		 * @param span
		 * @return int16_t
		 */
		int16_t ToInt16(base::ReadOnlySpan const &span);

		/**
		 * @brief 从 stream 中反序列化出 int16_t.
		 *
		 * @param stream
		 * @return int16_t
		 */
		int16_t ToInt16(base::Stream &stream);

		/**
		 * @brief 将高字节和低字节拼接成 uint16_t.
		 *
		 * @param high
		 * @param low
		 * @return uint16_t
		 */
		uint16_t ToUInt16(uint8_t high, uint8_t low);

		/**
		 * @brief 从 span 中反序列化出 uint32_t.
		 *
		 * @param span
		 * @return uint32_t
		 */
		uint32_t ToUInt32(base::ReadOnlySpan const &span);

		/**
		 * @brief 从 stream 中反序列化出 uint32_t.
		 *
		 * @param stream
		 * @return uint32_t
		 */
		uint32_t ToUInt32(base::Stream &stream);

		/**
		 * @brief 从 span 中反序列化出 int32_t.
		 *
		 * @param span
		 * @return int32_t
		 */
		int32_t ToInt32(base::ReadOnlySpan const &span);

		/**
		 * @brief 从 stream 中反序列化出 int32_t.
		 *
		 * @param stream
		 * @return int32_t
		 */
		int32_t ToInt32(base::Stream &stream);

		/**
		 * @brief 将 4 个字节拼接成 uint32_t. b0 是最低字节，b3 是最高字节。
		 *
		 * @param b3 最高字节
		 * @param b2
		 * @param b1
		 * @param b0 最低字节
		 * @return uint32_t
		 */
		uint32_t ToUInt32(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0);

		/**
		 * @brief 将低 uint16_t 和高 uint16_t 拼接成 uint32_t.
		 *
		 * @param high
		 * @param low
		 * @return uint32_t
		 */
		uint32_t ToUInt32(uint16_t high, uint16_t low);

		/**
		 * @brief 从 span 中反序列化出 uint64_t.
		 *
		 * @param span
		 * @return uint64_t
		 */
		uint64_t ToUInt64(base::ReadOnlySpan const &span);

		/**
		 * @brief 从 stream 中反序列化出 uint64_t.
		 *
		 * @param stream
		 * @return uint64_t
		 */
		uint64_t ToUInt64(base::Stream &stream);

		/**
		 * @brief 从 span 中反序列化出 int64_t.
		 *
		 * @param span
		 * @return int64_t
		 */
		int64_t ToInt64(base::ReadOnlySpan const &span);

		/**
		 * @brief 从 stream 中反序列化出 int64_t.
		 *
		 * @param stream
		 * @return int64_t
		 */
		int64_t ToInt64(base::Stream &stream);

		/**
		 * @brief 从 span 中反序列化出 float.
		 *
		 * @param span
		 * @return float
		 */
		float ToFloat(base::ReadOnlySpan const &span);

		/**
		 * @brief 从 stream 中反序列化出 float.
		 *
		 * @param stream
		 * @return float
		 */
		float ToFloat(base::Stream &stream);

		/**
		 * @brief 从 span 中反序列化出 double.
		 *
		 * @param span
		 * @return double
		 */
		double ToDouble(base::ReadOnlySpan const &span);

		/**
		 * @brief 从 stream 中反序列化出 double.
		 *
		 * @param stream
		 * @return double
		 */
		double ToDouble(base::Stream &stream);

		/* #region GetBytes */

		/**
		 * @brief 将 value 序列化，写入 span 中。
		 *
		 * @param value
		 * @param span
		 */
		void GetBytes(uint16_t value, base::Span const &span);

		/**
		 * @brief 将 value 序列化，写入 stream 中。
		 *
		 * @param value
		 * @param stream
		 */
		void GetBytes(uint16_t value, base::Stream &stream);

		/**
		 * @brief 将 value 序列化，写入 span 中。
		 *
		 * @param value
		 * @param span
		 */
		void GetBytes(int16_t value, base::Span const &span);

		/**
		 * @brief 将 value 序列化，写入 stream 中。
		 *
		 * @param value
		 * @param stream
		 */
		void GetBytes(int16_t value, base::Stream &stream);

		/**
		 * @brief 将 value 序列化，写入 span 中。
		 *
		 * @param value
		 * @param span
		 */
		void GetBytes(uint32_t value, base::Span const &span);

		/**
		 * @brief 将 value 序列化，写入 stream 中。
		 *
		 * @param value
		 * @param stream
		 */
		void GetBytes(uint32_t value, base::Stream &stream);

		/**
		 * @brief 将 value 序列化，写入 span 中。
		 *
		 * @param value
		 * @param span
		 */
		void GetBytes(int32_t value, base::Span const &span);

		/**
		 * @brief 将 value 序列化，写入 stream 中。
		 *
		 * @param value
		 * @param stream
		 */
		void GetBytes(int32_t value, base::Stream &stream);

		/**
		 * @brief 将 value 序列化，写入 span 中。
		 *
		 * @param value
		 * @param span
		 */
		void GetBytes(uint64_t value, base::Span const &span);

		/**
		 * @brief 将 value 序列化，写入 stream 中。
		 *
		 * @param value
		 * @param stream
		 */
		void GetBytes(uint64_t value, base::Stream &stream);

		/**
		 * @brief 将 value 序列化，写入 span 中。
		 *
		 * @param value
		 * @param span
		 */
		void GetBytes(int64_t value, base::Span const &span);

		/**
		 * @brief 将 value 序列化，写入 stream 中。
		 *
		 * @param value
		 * @param stream
		 */
		void GetBytes(int64_t value, base::Stream &stream);

		/**
		 * @brief 将 value 序列化，写入 span 中。
		 *
		 * @param value
		 * @param span
		 */
		void GetBytes(float value, base::Span const &span);

		/**
		 * @brief 将 value 序列化，写入 stream 中。
		 *
		 * @param value
		 * @param stream
		 */
		void GetBytes(float value, base::Stream &stream);

		/**
		 * @brief 将 value 序列化，写入 span 中。
		 *
		 * @param value
		 * @param span
		 */
		void GetBytes(double value, base::Span const &span);

		/**
		 * @brief 将 value 序列化，写入 stream 中。
		 *
		 * @param value
		 * @param stream
		 */
		void GetBytes(double value, base::Stream &stream);
		/* #endregion */

	} // namespace bit_converte
} // namespace base

#pragma once
#include <array>
#include <base/define.h>
#include <base/stream/ReadOnlySpan.h>
#include <base/stream/Stream.h>
#include <stdint.h>

namespace base
{
	/// @brief 比特转换
	class BitConverter
	{
	private:
		BitConverter() = delete;

	public:
#pragma region 转数字
		/// @brief 从缓冲区中 offset 处开始，反序列化出 uint16_t
		/// @param span
		/// @return
		static_function uint16_t ToUInt16(base::ReadOnlySpan const &span);

		/// @brief 从流中反序列化出数值。
		/// @param stream
		/// @return
		static_function uint16_t ToUInt16(base::Stream &stream);

		/// @brief 从缓冲区中 offset 处开始，反序列化出 int16_t
		/// @param span
		/// @return
		static_function int16_t ToInt16(base::ReadOnlySpan const &span);

		/// @brief 从流中反序列化出数值。
		/// @param stream
		/// @return
		static_function int16_t ToInt16(base::Stream &stream);

		/// @brief 将高字节和低字节拼接成 uint16_t.
		/// @param high
		/// @param low
		/// @return
		static_function uint16_t ToUInt16(uint8_t high, uint8_t low);

		/// @brief 从缓冲区中 offset 处开始，反序列化出 uint32_t
		/// @param span
		/// @return
		static_function uint32_t ToUInt32(base::ReadOnlySpan const &span);

		/// @brief 从流中反序列化出数值。
		/// @param stream
		/// @return
		static_function uint32_t ToUInt32(base::Stream &stream);

		/// @brief 从缓冲区中 offset 处开始，反序列化出 int32_t
		/// @param span
		/// @return
		static_function int32_t ToInt32(base::ReadOnlySpan const &span);

		/// @brief 从流中反序列化出数值。
		/// @param stream
		/// @return
		static_function int32_t ToInt32(base::Stream &stream);

		/// @brief 将 4 个字节拼接成 uint32_t. b0 是最低字节，b3 是最高字节。
		/// @param b3 最高字节
		/// @param b2
		/// @param b1
		/// @param b0 最低字节
		/// @return
		static_function uint32_t ToUInt32(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0);

		/// @brief 将低 uint16_t 和高 uint16_t 拼接成 uint32_t.
		/// @param high
		/// @param low
		/// @return
		static_function uint32_t ToUInt32(uint16_t high, uint16_t low);

		/// @brief 从缓冲区中 offset 处开始，反序列化出 uint64_t
		/// @param span
		/// @return
		static_function uint64_t ToUInt64(base::ReadOnlySpan const &span);

		/// @brief 从流中反序列化出数值。
		/// @param stream
		/// @return
		static_function uint64_t ToUInt64(base::Stream &stream);

		/// @brief 从缓冲区中 offset 处开始，反序列化出 int64_t
		/// @param span
		/// @return
		static_function int64_t ToInt64(base::ReadOnlySpan const &span);

		/// @brief 从流中反序列化出数值。
		/// @param stream
		/// @return
		static_function int64_t ToInt64(base::Stream &stream);

		/// @brief 从缓冲区中 offset 处开始，反序列化出 float
		/// @param span
		/// @return
		static_function float ToFloat(base::ReadOnlySpan const &span);

		/// @brief 从流中反序列化出数值。
		/// @param stream
		/// @return
		static_function float ToFloat(base::Stream &stream);

		/// @brief 从缓冲区中 offset 处开始，反序列化出 double
		/// @param span
		/// @return
		static_function double ToDouble(base::ReadOnlySpan const &span);

		/// @brief 从流中反序列化出数值。
		/// @param stream
		/// @return
		static_function double ToDouble(base::Stream &stream);
#pragma endregion

#pragma region 转到缓冲区
		/// @brief 将 value 序列化到缓冲区中的 offset 处。
		/// @param value
		/// @param span
		static_function void GetBytes(uint16_t value, base::Span const &span);

		/// @brief 将 value 序列化到流中。
		/// @param value
		/// @param stream
		/// @return
		static_function void GetBytes(uint16_t value, base::Stream &stream);

		/// @brief 将 value 序列化到缓冲区中的 offset 处。
		/// @param value
		/// @param span
		static_function void GetBytes(int16_t value, base::Span const &span);

		/// @brief 将 value 序列化到流中。
		/// @param value
		/// @param stream
		/// @return
		static_function void GetBytes(int16_t value, base::Stream &stream);

		/// @brief 将 value 序列化到缓冲区中的 offset 处。
		/// @param value
		/// @param span
		static_function void GetBytes(uint32_t value, base::Span const &span);

		/// @brief 将 value 序列化到流中。
		/// @param value
		/// @param stream
		/// @return
		static_function void GetBytes(uint32_t value, base::Stream &stream);

		/// @brief 将 value 序列化到缓冲区中的 offset 处。
		/// @param value
		/// @param span
		static_function void GetBytes(int32_t value, base::Span const &span);

		/// @brief 将 value 序列化到流中。
		/// @param value
		/// @param stream
		/// @return
		static_function void GetBytes(int32_t value, base::Stream &stream);

		/// @brief 将 value 序列化到缓冲区中的 offset 处。
		/// @param value
		/// @param span
		static_function void GetBytes(uint64_t value, base::Span const &span);

		/// @brief 将 value 序列化到流中。
		/// @param value
		/// @param stream
		/// @return
		static_function void GetBytes(uint64_t value, base::Stream &stream);

		/// @brief 将 value 序列化到缓冲区中的 offset 处。
		/// @param value
		/// @param span
		static_function void GetBytes(int64_t value, base::Span const &span);

		/// @brief 将 value 序列化到流中。
		/// @param value
		/// @param stream
		/// @return
		static_function void GetBytes(int64_t value, base::Stream &stream);

		/// @brief 将 value 序列化到缓冲区中的 offset 处。
		/// @param value
		/// @param span
		static_function void GetBytes(float value, base::Span const &span);

		/// @brief 将 value 序列化到流中。
		/// @param value
		/// @param stream
		/// @return
		static_function void GetBytes(float value, base::Stream &stream);

		/// @brief 将 value 序列化到缓冲区中的 offset 处。
		/// @param value
		/// @param span
		static_function void GetBytes(double value, base::Span const &span);

		/// @brief 将 value 序列化到流中。
		/// @param value
		/// @param stream
		/// @return
		static_function void GetBytes(double value, base::Stream &stream);
#pragma endregion
	};
} // namespace base

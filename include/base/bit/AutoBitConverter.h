#pragma once
#include <array>
#include <base/stream/ReadOnlySpan.h>
#include <base/stream/Stream.h>
#include <bit>
#include <stdint.h>

namespace base
{
	/// @brief 构造时设置好通信对方的大小端，进行转换时能够自动进行大小端转换。
	class AutoBitConverter final
	{
	private:
		std::endian _remote_endian;

	public:
		/// @brief
		/// @param remote_endian 对方主机的字节序
		AutoBitConverter(std::endian remote_endian);

		/// @brief 是否应该翻转。
		/// @return 当远程字节序和本机字节序不同时，需要翻转，此时会返回 true.
		bool ShouldReverse() const;

		/// @brief 从缓冲区中 offset 处开始，反序列化出 uint16_t
		/// @param span
		/// @return
		uint16_t ToUInt16(base::ReadOnlySpan const &span) const;

		/// @brief 从流中反序列化出数值。
		/// @param stream
		/// @return
		uint16_t ToUInt16(base::Stream &stream) const;

		/// @brief 从缓冲区中 offset 处开始，反序列化出 int16_t
		/// @param span
		/// @return
		int16_t ToInt16(base::ReadOnlySpan const &span) const;

		/// @brief 从流中反序列化出数值。
		/// @param stream
		/// @return
		int16_t ToInt16(base::Stream &stream) const;

		/// @brief 将高字节和低字节拼接成 uint16_t.
		/// @param high
		/// @param low
		/// @return
		uint16_t ToUInt16(uint8_t high, uint8_t low) const;

		/// @brief 从缓冲区中 offset 处开始，反序列化出 uint32_t
		/// @param span
		/// @return
		uint32_t ToUInt32(base::ReadOnlySpan const &span) const;

		/// @brief 从流中反序列化出数值。
		/// @param stream
		/// @return
		uint32_t ToUInt32(base::Stream &stream) const;

		/// @brief 从缓冲区中 offset 处开始，反序列化出 int32_t
		/// @param span
		/// @return
		int32_t ToInt32(base::ReadOnlySpan const &span) const;

		/// @brief 从流中反序列化出数值。
		/// @param stream
		/// @return
		int32_t ToInt32(base::Stream &stream) const;

		/// @brief 将 4 个字节拼接成 uint32_t. b0 是最低字节，b3 是最高字节。
		/// @param b3 最高字节
		/// @param b2
		/// @param b1
		/// @param b0 最低字节
		/// @return
		uint32_t ToUInt32(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0) const;

		/// @brief 将低 uint16_t 和高 uint16_t 拼接成 uint32_t.
		/// @param high
		/// @param low
		/// @return
		uint32_t ToUInt32(uint16_t high, uint16_t low) const;

		/// @brief 从缓冲区中 offset 处开始，反序列化出 uint64_t
		/// @param span
		/// @return
		uint64_t ToUInt64(base::ReadOnlySpan const &span) const;

		/// @brief 从流中反序列化出数值。
		/// @param stream
		/// @return
		uint64_t ToUInt64(base::Stream &stream) const;

		/// @brief 从缓冲区中 offset 处开始，反序列化出 int64_t
		/// @param span
		/// @return
		int64_t ToInt64(base::ReadOnlySpan const &span) const;

		/// @brief 从流中反序列化出数值。
		/// @param stream
		/// @return
		int64_t ToInt64(base::Stream &stream) const;

		/// @brief 从缓冲区中 offset 处开始，反序列化出 float
		/// @param span
		/// @return
		float ToFloat(base::ReadOnlySpan const &span) const;

		/// @brief 从流中反序列化出数值。
		/// @param stream
		/// @return
		float ToFloat(base::Stream &stream) const;

		/// @brief 从缓冲区中 offset 处开始，反序列化出 double
		/// @param span
		/// @return
		double ToDouble(base::ReadOnlySpan const &span) const;

		/// @brief 从流中反序列化出数值。
		/// @param stream
		/// @return
		double ToDouble(base::Stream &stream) const;

		/// @brief 将 value 序列化到缓冲区中的 offset 处。
		/// @param value
		/// @param span
		void GetBytes(uint16_t value, base::Span const &span) const;

		/// @brief 将 value 序列化到流中。
		/// @param value
		/// @param stream
		/// @return
		void GetBytes(uint16_t value, base::Stream &stream) const;

		/// @brief 将 value 序列化到缓冲区中的 offset 处。
		/// @param value
		/// @param span
		void GetBytes(int16_t value, base::Span const &span) const;

		/// @brief 将 value 序列化到流中。
		/// @param value
		/// @param stream
		/// @return
		void GetBytes(int16_t value, base::Stream &stream) const;

		/// @brief 将 value 序列化到缓冲区中的 offset 处。
		/// @param value
		/// @param span
		void GetBytes(uint32_t value, base::Span const &span) const;

		/// @brief 将 value 序列化到流中。
		/// @param value
		/// @param stream
		/// @return
		void GetBytes(uint32_t value, base::Stream &stream) const;

		/// @brief 将 value 序列化到缓冲区中的 offset 处。
		/// @param value
		/// @param span
		void GetBytes(int32_t value, base::Span const &span) const;

		/// @brief 将 value 序列化到流中。
		/// @param value
		/// @param stream
		/// @return
		void GetBytes(int32_t value, base::Stream &stream) const;

		/// @brief 将 value 序列化到缓冲区中的 offset 处。
		/// @param value
		/// @param span
		void GetBytes(uint64_t value, base::Span const &span) const;

		/// @brief 将 value 序列化到流中。
		/// @param value
		/// @param stream
		/// @return
		void GetBytes(uint64_t value, base::Stream &stream) const;

		/// @brief 将 value 序列化到缓冲区中的 offset 处。
		/// @param value
		/// @param span
		void GetBytes(int64_t value, base::Span const &span) const;

		/// @brief 将 value 序列化到流中。
		/// @param value
		/// @param stream
		/// @return
		void GetBytes(int64_t value, base::Stream &stream) const;

		/// @brief 将 value 序列化到缓冲区中的 offset 处。
		/// @param value
		/// @param span
		void GetBytes(float value, base::Span const &span) const;

		/// @brief 将 value 序列化到流中。
		/// @param value
		/// @param stream
		/// @return
		void GetBytes(float value, base::Stream &stream) const;

		/// @brief 将 value 序列化到缓冲区中的 offset 处。
		/// @param value
		/// @param span
		void GetBytes(double value, base::Span const &span) const;

		/// @brief 将 value 序列化到流中。
		/// @param value
		/// @param stream
		/// @return
		void GetBytes(double value, base::Stream &stream) const;
	};
} // namespace base

#pragma once
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/stream/Stream.h"
#include "base/string/define.h"
#include <algorithm>
#include <cstdint>
#include <stdexcept>

namespace base::bit_converte
{
	/* #region FromBytes */

	///
	/// @brief 从字节序列中反序列化出 ReturnType.
	///
	/// @param span
	///
	/// @return
	///
	template <typename ReturnType>
	ReturnType FromBytes(base::ReadOnlySpan const &span)
	{
		if (span.Size() != static_cast<int64_t>(sizeof(ReturnType)))
		{
			throw std::invalid_argument{CODE_POS_STR + "传入的 span 大小不符。"};
		}

		ReturnType ret{};

		std::copy(span.Buffer(),
				  span.Buffer() + sizeof(ReturnType),
				  reinterpret_cast<uint8_t *>(&ret));

		return ret;
	}

	///
	/// @brief 从流中反序列化出 ReturnType.
	///
	/// @param stream
	///
	/// @return
	///
	template <typename ReturnType>
	ReturnType FromBytes(base::Stream &stream)
	{
		uint8_t buffer[sizeof(ReturnType)];

		base::Span span{
			buffer,
			static_cast<int64_t>(sizeof(ReturnType)),
		};

		int64_t have_read = stream.ReadExactly(span);
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
		if (span.Size() != static_cast<int64_t>(sizeof(ValueType)))
		{
			throw std::invalid_argument{CODE_POS_STR + "传入的 span 大小不符。"};
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
		stream.Write(buffer, 0, sizeof(ValueType));
	}

	/* #endregion */

	/* #region 转换为数值类型 */

	///
	/// @brief 将高字节和低字节拼接成 uint16_t.
	///
	/// @param high
	/// @param low
	///
	/// @return
	///
	constexpr uint16_t ToUInt16(uint8_t high, uint8_t low)
	{
		return (static_cast<uint16_t>(high) << 8) | low;
	}

	///
	/// @brief 将低 uint16_t 和高 uint16_t 拼接成 uint32_t.
	///
	/// @param high
	/// @param low
	///
	/// @return
	///
	constexpr uint32_t ToUInt32(uint16_t high, uint16_t low)
	{
		return (static_cast<uint32_t>(high) << 16) | low;
	}

	///
	/// @brief 将 4 个字节拼接成 uint32_t. b0 是最低字节，b3 是最高字节。
	///
	/// @param b3 最高字节
	/// @param b2
	/// @param b1
	/// @param b0 最低字节
	///
	/// @return
	///
	constexpr uint32_t ToUInt32(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0)
	{
		uint16_t high = ToUInt16(b3, b2);
		uint16_t low = ToUInt16(b1, b0);
		return ToUInt32(high, low);
	}

	/* #endregion */

} // namespace base::bit_converte

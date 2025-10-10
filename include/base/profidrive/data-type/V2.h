#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/bit/bit.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include <cstdint>

namespace base::profidrive
{
	///
	/// @brief 大端序的 16 个位集合。
	///
	///
	class V2
	{
	private:
		uint16_t _value = 0;

	public:
		/* #region 构造函数 */

		constexpr V2() = default;

		///
		/// @brief 从大端序的字节序列中构造。
		///
		/// @param span 将接收到的大端序的 16 位集缓冲区原封不动传进来。
		///
		explicit V2(base::ReadOnlySpan const &span)
		{
			_value = base::big_endian_remote_converter.FromBytes<uint16_t>(span);
		}

		///
		/// @brief 从位集中构造。
		///
		/// @param set
		///
		constexpr explicit V2(uint16_t value)
		{
			_value = value;
		}

		/* #endregion */

		constexpr uint16_t Value() const
		{
			return _value;
		}

		///
		/// @brief 获取指定位的值。
		///
		/// @param index
		/// @return
		///
		constexpr bool ReadBit(int32_t index) const
		{
			return base::bit::ReadBit(_value, index);
		}

		///
		/// @brief 设置指定位的值。
		///
		/// @param index
		/// @param value
		///
		constexpr void WriteBit(int32_t index, bool value)
		{
			base::bit::WriteBit(_value, index, value);
		}

		///
		/// @brief 读取指定范围内的位。
		///
		/// @param begin
		/// @param end
		/// @return
		///
		constexpr uint16_t ReadBits(int32_t begin, int32_t end) const
		{
			return base::bit::ReadBits(_value, begin, end);
		}

		///
		/// @brief 写入指定范围内的位。
		///
		/// @param begin
		/// @param end
		/// @param value
		///
		constexpr void WriteBits(int32_t begin, int32_t end, uint16_t value)
		{
			base::bit::WriteBits(_value, begin, end, value);
		}

		///
		/// @brief 将本对象序列化为字节序列，可以被发送到 profinet.
		///
		/// @param span
		///
		void GetBytes(base::Span const &span) const
		{
			if (span.Size() < 2)
			{
				throw std::invalid_argument{CODE_POS_STR + "传入的内存段过小。"};
			}

			base::big_endian_remote_converter.GetBytes(_value, span);
		}

		///
		/// @brief 强制转换为 uint16_t.
		///
		/// @note 注意，里面的位是小端序。即 V2 的 bit0 在返回的 uint16_t
		/// 中的 bit0, V2 的 bit8 在返回的 uint16_t 中的 bit8.
		///
		/// @return
		///
		constexpr explicit operator uint16_t() const
		{
			return _value;
		}
	};

} // namespace base::profidrive

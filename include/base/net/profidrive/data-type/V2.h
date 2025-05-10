#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/container/Array.h"
#include "base/stream/ReadOnlySpan.h"
#include <bitset>
#include <cstdint>

namespace base
{
	namespace profidrive
	{
		///
		/// @brief 大端序的 16 个位集合。
		///
		///
		class V2
		{
		private:
			std::bitset<16> _bitset;
			base::AutoBitConverter _converter{std::endian::big};

		public:
			/* #region 构造函数 */

			V2() = default;

			///
			/// @brief 从大端序的字节序列中构造。
			///
			/// @param span 将接收到的大端序的 16 位集缓冲区原封不动传进来。
			///
			explicit V2(base::ReadOnlySpan const &span)
			{
				// 经过转换后，变成小端序了，第 1 个字节是 bit0 到 bit7，第 2 个字节是 bit8 到 bit15.
				uint16_t data = _converter.FromBytes<uint16_t>(span);
				for (int i = 0; i < 16; i++)
				{
					_bitset[i] = data & (1 << i);
				}
			}

			///
			/// @brief 从位集中构造。
			///
			/// @param set
			///
			explicit V2(std::bitset<16> const &set)
			{
				_bitset = set;
			}

			/* #endregion */

			std::bitset<16> const &Bitset() const
			{
				return _bitset;
			}

			///
			/// @brief 索引指定位。
			///
			/// @param index
			/// @return decltype(_bitset[index])
			///
			auto operator[](int32_t index) -> decltype(_bitset[index])
			{
				auto ret = _bitset[index];
				return ret;
			}

			///
			/// @brief 索引指定位。
			///
			/// @param index
			/// @return decltype(_bitset[index])
			///
			auto operator[](int32_t index) const -> decltype(_bitset[index])
			{
				return _bitset[index];
			}

			base::Array<uint8_t, 2> BufferForSending() const
			{
				uint16_t data = _bitset.to_ulong();
				base::Array<uint8_t, 2> buffer;
				_converter.GetBytes(data, buffer.Span());
				return buffer;
			}
		};
	} // namespace profidrive
} // namespace base

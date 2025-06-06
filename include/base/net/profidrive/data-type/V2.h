#pragma once
#include "base/bit/AutoBitConverter.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
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

				uint16_t raw_value = _bitset.to_ulong();
				_converter.GetBytes(raw_value, span);
			}

			///
			/// @brief 强制转换为 uint16_t.
			///
			/// @note 注意，里面的位是小端序。即 V2 的 bit0 在返回的 uint16_t
			/// 中的 bit0, V2 的 bit8 在返回的 uint16_t 中的 bit8.
			///
			/// @return
			///
			explicit operator uint16_t() const
			{
				return _bitset.to_ulong();
			}
		};
	} // namespace profidrive
} // namespace base

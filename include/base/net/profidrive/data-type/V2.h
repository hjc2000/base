#pragma once
#include <base/bit/AutoBitConverter.h>
#include <base/container/Array.h>
#include <base/stream/ReadOnlySpan.h>
#include <bitset>

namespace base
{
	namespace profidrive
	{
		/**
		 * @brief 大端序的 16 个位集合。
		 *
		 */
		class V2
		{
		private:
			/**
			 * @brief 大端序的可直接用于发送的 16 位集缓冲区。
			 *
			 */
			base::Array<uint8_t, 2> _buffer;
			base::AutoBitConverter _converter{std::endian::big};

		public:
			V2() = default;

			/**
			 * @brief 从大端序的字节序列中构造。
			 *
			 * @param span 将接收到的大端序的 16 位集缓冲区原封不动传进来。
			 */
			V2(base::ReadOnlySpan const &span);

			/**
			 * @brief 从位集中构造。
			 *
			 * @param set
			 */
			V2(std::bitset<16> const &set);

		public:
			/**
			 * @brief 强制转换为位集。
			 *
			 * @return std::bitset<16>
			 */
			explicit operator std::bitset<16>() const;

			/**
			 * @brief 转换为 std::bitset<16>.
			 *
			 * @return std::bitset<16>
			 */
			std::bitset<16> ToBitSet() const;

			/**
			 * @brief 大端序的可直接用于发送的 16 位集缓冲区。
			 *
			 * @return base::Span
			 */
			base::Span Span();
		};
	} // namespace profidrive
} // namespace base

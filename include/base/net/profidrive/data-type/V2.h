#pragma once
#include <base/bit/AutoBitConverter.h>
#include <base/container/Array.h>
#include <base/stream/ReadOnlySpan.h>
#include <bitset>
#include <cstdint>

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
			std::bitset<16> _bitset;
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

			base::Array<uint8_t, 2> BufferForSending() const;

		public:
			/**
			 * @brief 索引指定位。
			 *
			 * @param index
			 * @return decltype(_bitset[index])
			 */
			auto operator[](int32_t index) -> decltype(_bitset[index]);

			/**
			 * @brief 索引指定位。
			 *
			 * @param index
			 * @return decltype(_bitset[index])
			 */
			auto operator[](int32_t index) const -> decltype(_bitset[index]);
		};
	} // namespace profidrive
} // namespace base

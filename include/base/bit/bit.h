#pragma once
#include "base/string/define.h"
#include <bit>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <type_traits>

namespace base
{
	namespace bit
	{
		/* #region 检查参数合法性 */

		template <typename RegisterType>
		constexpr void CheckBitIndex(int bit_index)
		{
			if (bit_index < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "位索引不能 < 0."};
			}

			if (bit_index >= static_cast<int>(8 * sizeof(RegisterType)))
			{
				throw std::invalid_argument{CODE_POS_STR + "位索引不能 >= 64."};
			}
		}

		template <typename RegisterType>
		constexpr void CheckBitRange(int begin, int end)
		{
			if (begin < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "begin 不能 < 0."};
			}

			if (begin >= static_cast<int>(8 * sizeof(RegisterType)))
			{
				throw std::invalid_argument{CODE_POS_STR + "begin 不能 >= 64."};
			}

			if (end < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "end 不能 < 0."};
			}

			if (end > static_cast<int>(8 * sizeof(RegisterType)))
			{
				throw std::invalid_argument{CODE_POS_STR + "end 不能 > 64."};
			}

			if (begin > end)
			{
				throw std::invalid_argument{CODE_POS_STR + "begin 不能 > end."};
			}
		}

		/* #endregion */

		///
		/// @brief 从最高位开始数，有多少个连续的 0.
		///
		/// @param num
		/// @return
		///
		template <typename RegisterType>
			requires(std::is_integral_v<RegisterType>)
		constexpr int HighZeroCount(RegisterType num)
		{
			return std::countl_zero(num);
		}

		///
		/// @brief 最高位的 1 的索引。
		///
		/// @note 例如 0x1 的 bit0 是最高位的 1，于是返回 0.
		///
		/// @param num
		/// @return
		///
		template <typename RegisterType>
			requires(std::is_integral_v<RegisterType>)
		constexpr int HighestOneBitIndex(RegisterType num)
		{
			int count = HighZeroCount(num);
			return sizeof(num) * 8 - count - 1;
		}

		///
		/// @brief 将 num 进行左对齐。
		///
		/// @note 即将 num 进行左移位，使最高位的 1 位于最高有效位，即去除所有的前导 0.
		///
		/// @param num
		/// @return
		///
		template <typename RegisterType>
			requires(std::is_integral_v<RegisterType>)
		constexpr uint8_t AlignToLeft(RegisterType num)
		{
			return num << HighZeroCount(num);
		}

		/* #region 掩码 */

		///
		/// @brief 获取一个只有 bit_index 指定的位为 1, 其他位都为 0 的掩码。
		///
		/// @param bit_index
		/// @return
		///
		constexpr uint64_t Bit(int bit_index)
		{
			CheckBitIndex<uint64_t>(bit_index);
			return static_cast<uint64_t>(0b1) << bit_index;
		}

		///
		/// @brief 最低有效位。
		///
		///
		template <typename RegisterType>
			requires(std::is_integral_v<RegisterType>)
		constexpr RegisterType LSB()
		{
			return static_cast<RegisterType>(1);
		}

		///
		/// @brief 最高有效位。
		///
		///
		template <typename RegisterType>
			requires(std::is_integral_v<RegisterType>)
		constexpr RegisterType MSB()
		{
			uint8_t bit_count = sizeof(RegisterType) * 8;
			return static_cast<RegisterType>(base::bit::Bit(bit_count - 1));
		}

		///
		/// @brief 获取位掩码。其中指定范围内的位为 1, 其他位为 0.
		/// 	@note 是一个左闭右开区间。
		///
		/// @param begin 起始索引。左端点是闭的。
		/// @param end 结束索引。右端点是开的。
		///
		/// @return
		///
		constexpr uint64_t BitMask(int begin, int end)
		{
			CheckBitRange<uint64_t>(begin, end);
			uint64_t ret = 0;
			for (int i = begin; i < end; i++)
			{
				ret |= Bit(i);
			}

			return ret;
		}

		/* #endregion */

		/* #region 置位 */

		///
		/// @brief 置位指定的位。
		///
		/// @param reg 寄存器。
		/// 	@note 其实就是普通的整型，只要是整型都可以。寄存器也可以强制转换成整型的指针，
		/// 	解引用后传进来。
		///
		/// @param bit_index 要置位的位的索引。
		///
		template <typename RegisterType>
			requires(std::is_integral_v<RegisterType>)
		constexpr void SetBit(RegisterType &reg, int bit_index)
		{
			CheckBitIndex<RegisterType>(bit_index);
			reg |= Bit(bit_index);
		}

		///
		/// @brief 将指定范围内的位置位。
		///
		/// @param reg 寄存器。
		/// @param begin 要置位的区间起点。闭端点。
		/// @param end 要置位的区间终点。开端点。
		///
		template <typename RegisterType>
			requires(std::is_integral_v<RegisterType>)
		constexpr void SetBits(RegisterType &reg, int begin, int end)
		{
			CheckBitRange<RegisterType>(begin, end);
			reg |= BitMask(begin, end);
		}

		/* #endregion */

		/* #region 复位 */

		///
		/// @brief 复位指定的位。
		///
		/// @param reg 寄存器。
		/// 	@note 其实就是普通的整型，只要是整型都可以。寄存器也可以强制转换成整型的指针，
		/// 	解引用后传进来。
		///
		/// @param bit_index 要复位的位的索引。
		///
		template <typename RegisterType>
			requires(std::is_integral_v<RegisterType>)
		constexpr void ResetBit(RegisterType &reg, int bit_index)
		{
			CheckBitIndex<RegisterType>(bit_index);
			reg &= ~Bit(bit_index);
		}

		///
		/// @brief 将指定范围内的位复位（置成 0.）。
		///
		/// @param reg 寄存器。
		/// @param begin 要复位的区间起点。闭端点。
		/// @param end 要复位的区间终点。开端点。
		///
		template <typename RegisterType>
			requires(std::is_integral_v<RegisterType>)
		constexpr void ResetBits(RegisterType &reg, int begin, int end)
		{
			CheckBitRange<RegisterType>(begin, end);
			reg &= ~BitMask(begin, end);
		}

		/* #endregion */

		/* #region 读位 */

		///
		/// @brief 读取指定位的值。
		///
		/// @param reg 寄存器。
		/// @param bit_index 要读取的位的索引。
		///
		/// @return
		///
		template <typename RegisterType>
			requires(std::is_integral_v<RegisterType>)
		constexpr bool ReadBit(RegisterType const &reg, int bit_index)
		{
			CheckBitIndex<RegisterType>(bit_index);
			return reg & Bit(bit_index);
		}

		///
		/// @brief 读取指定范围内的位。
		/// 	@note 读取后会将取出的这些位移动到与最低位对齐。
		///
		/// @param reg
		/// @param begin
		/// @param end
		/// @return
		///
		template <typename RegisterType>
			requires(std::is_integral_v<RegisterType>)
		constexpr RegisterType ReadBits(RegisterType const &reg, int begin, int end)
		{
			CheckBitRange<RegisterType>(begin, end);
			RegisterType ret = reg & BitMask(begin, end);
			ret >>= begin;
			return ret;
		}

		/* #endregion */

		/* #region 写位 */

		///
		/// @brief 向指定索引的位写入值。
		///
		/// @param reg
		/// @param bit_index
		/// @param value
		/// @return
		///
		template <typename RegisterType>
			requires(std::is_integral_v<RegisterType>)
		constexpr void WriteBit(RegisterType &reg, int bit_index, bool value)
		{
			CheckBitIndex<RegisterType>(bit_index);
			if (value)
			{
				SetBit(reg, bit_index);
			}
			else
			{
				ResetBit(reg, bit_index);
			}
		}

		///
		/// @brief 将值写入寄存器指定的位范围。
		///
		/// @param reg 寄存器。
		/// @param begin 位范围起始。闭端点。
		/// @param end 位范围结束。开端点。
		/// @param value 要写入 reg 的指定范围内的值。
		///
		template <typename RegisterType>
			requires(std::is_integral_v<RegisterType>)
		constexpr void WriteBits(RegisterType &reg, int begin, int end, uint64_t value)
		{
			CheckBitRange<RegisterType>(begin, end);

			// 将值移位，与要写入的寄存器位置对齐。
			value <<= begin;
			uint64_t bit_mask = base::bit::BitMask(begin, end);
			value &= bit_mask;

			// 将要写入的范围先清零
			reg &= ~bit_mask;

			// 通过按位或运算写入这些位。
			reg |= value;
		}

		/* #endregion */

		///
		/// @brief 将 address 向上调整到 align_byte_count 字节对齐的地址。
		///
		/// @param address
		/// @param align_byte_count
		/// @return
		///
		template <typename AddressType>
			requires(std::is_same_v<AddressType, size_t> || std::is_same_v<AddressType, uint8_t *>)
		constexpr AddressType AlignUp(AddressType address, size_t align_byte_count = 8)
		{
			size_t size = reinterpret_cast<size_t>(address);
			size_t mod = size % align_byte_count;
			size_t aligned_size = (size / align_byte_count) * align_byte_count;
			if (mod > 0)
			{
				aligned_size += align_byte_count;
			}

			return reinterpret_cast<AddressType>(aligned_size);
		}

		///
		/// @brief 将 address 向下调整到 align_byte_count 字节对齐的地址。
		///
		/// @param address
		/// @param align_byte_count
		/// @return
		///
		template <typename AddressType>
			requires(std::is_same_v<AddressType, size_t> || std::is_same_v<AddressType, uint8_t *>)
		constexpr AddressType AlignDown(AddressType address, size_t align_byte_count = 8)
		{
			size_t size = reinterpret_cast<size_t>(address);
			size_t aligned_size = (size / align_byte_count) * align_byte_count;
			return reinterpret_cast<AddressType>(aligned_size);
		}

		///
		/// @brief 获取指定类型的对齐后的大小。
		///
		/// @return
		///
		template <typename T, size_t AlignByteCount = 8>
		constexpr size_t GetAlignedSize()
		{
			return base::bit::AlignUp(sizeof(T), AlignByteCount);
		}

		///
		/// @brief 翻转位。
		///
		/// @note 翻转后，最低位位将变为最高位，最高位将变为最低位。
		///
		///
		template <typename T>
			requires(std::is_integral_v<T>)
		constexpr T Reverse(T value)
		{
			int32_t bit_count = sizeof(T) * 8;
			for (int32_t i = 0; i < bit_count / 2; i++)
			{
				int32_t left_index = bit_count - 1 - i;
				int32_t right_index = i;
				bool left_bit = base::bit::ReadBit(value, left_index);
				bool right_bit = base::bit::ReadBit(value, right_index);
				base::bit::WriteBit(value, left_index, right_bit);
				base::bit::WriteBit(value, right_index, left_bit);
			}

			return value;
		}

	} // namespace bit
} // namespace base

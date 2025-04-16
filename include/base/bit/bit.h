#pragma once
#include "base/string/define.h"
#include <bit>
#include <cstdint>
#include <stdexcept>
#include <type_traits>

namespace base
{
	namespace bit
	{
		template <typename RegisterType>
		constexpr void CheckBitIndex(int index)
		{
			if (index < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "位索引不能 < 0."};
			}

			if (index >= static_cast<int>(8 * sizeof(RegisterType)))
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

		///
		/// @brief 从最高位开始数，有多少个连续的 0.
		///
		/// @param num
		/// @return
		///
		constexpr int HighZeroCount(uint8_t num)
		{
			return std::countl_zero(num);
		}

		///
		/// @brief 从最高位开始数，有多少个连续的 0.
		///
		/// @param num
		/// @return
		///
		constexpr int HighZeroCount(uint16_t num)
		{
			return std::countl_zero(num);
		}

		///
		/// @brief 从最高位开始数，有多少个连续的 0.
		///
		/// @param num
		/// @return
		///
		constexpr int HighZeroCount(uint32_t num)
		{
			return std::countl_zero(num);
		}

		///
		/// @brief 从最高位开始数，有多少个连续的 0.
		///
		/// @param num
		/// @return
		///
		constexpr int HighZeroCount(uint64_t num)
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
		constexpr int HighestOneBitIndex(uint8_t num)
		{
			int count = HighZeroCount(num);
			return 8 - count - 1;
		}

		///
		/// @brief 最高位的 1 的索引。
		///
		/// @note 例如 0x1 的 bit0 是最高位的 1，于是返回 0.
		///
		/// @param num
		/// @return
		///
		constexpr int HighestOneBitIndex(uint16_t num)
		{
			int count = HighZeroCount(num);
			return 16 - count - 1;
		}

		///
		/// @brief 最高位的 1 的索引。
		///
		/// @note 例如 0x1 的 bit0 是最高位的 1，于是返回 0.
		///
		/// @param num
		/// @return
		///
		constexpr int HighestOneBitIndex(uint32_t num)
		{
			int count = HighZeroCount(num);
			return 32 - count - 1;
		}

		///
		/// @brief 最高位的 1 的索引。
		///
		/// @note 例如 0x1 的 bit0 是最高位的 1，于是返回 0.
		///
		/// @param num
		/// @return
		///
		constexpr int HighestOneBitIndex(uint64_t num)
		{
			int count = HighZeroCount(num);
			return 64 - count - 1;
		}

		///
		/// @brief 将 num 进行左对齐。
		///
		/// @note 即将 num 进行左移位，使最高位的 1 位于最高有效位，即去除所有的前导 0.
		///
		/// @param num
		/// @return
		///
		constexpr uint8_t AlignToLeft(uint8_t num)
		{
			return num << HighZeroCount(num);
		}

		///
		/// @brief 将 num 进行左对齐。
		///
		/// @note 即将 num 进行左移位，使最高位的 1 位于最高有效位，即去除所有的前导 0.
		///
		/// @param num
		/// @return
		///
		constexpr uint16_t AlignToLeft(uint16_t num)
		{
			return num << HighZeroCount(num);
		}

		///
		/// @brief 将 num 进行左对齐。
		///
		/// @note 即将 num 进行左移位，使最高位的 1 位于最高有效位，即去除所有的前导 0.
		///
		/// @param num
		/// @return
		///
		constexpr uint32_t AlignToLeft(uint32_t num)
		{
			return num << HighZeroCount(num);
		}

		///
		/// @brief 将 num 进行左对齐。
		///
		/// @note 即将 num 进行左移位，使最高位的 1 位于最高有效位，即去除所有的前导 0.
		///
		/// @param num
		/// @return
		///
		constexpr uint64_t AlignToLeft(uint64_t num)
		{
			return num << HighZeroCount(num);
		}

		///
		/// @brief 获取一个只有 bit_index 指定的位为 1, 其他位都为 0 的掩码。
		///
		/// @param bit_index
		/// @return
		///
		constexpr uint64_t Bit(int bit_index)
		{
			CheckBitIndex<uint64_t>(bit_index);
			return 0b1 << bit_index;
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

		///
		/// @brief 置位指定的位。
		///
		/// @param reg 寄存器。
		/// 	@note 其实就是普通的整型，只要是整型都可以。寄存器也可以强制转换成整型的指针，
		/// 	解引用后传进来。
		///
		/// @param bit_index 要置位的位的索引。
		///
		template <typename RegisterType, std::enable_if_t<std::is_integral_v<RegisterType>, int> = 0>
		constexpr void SetBit(RegisterType &reg, int bit_index)
		{
			CheckBitIndex<RegisterType>(bit_index);
			reg |= Bit(bit_index);
		}

		template <typename RegisterType, std::enable_if_t<std::is_integral_v<RegisterType>, int> = 0>
		constexpr void SetBits(RegisterType &reg, int begin, int end)
		{
			CheckBitRange<RegisterType>(begin, end);
			reg |= BitMask(begin, end);
		}

		///
		/// @brief 复位指定的位。
		///
		/// @param reg 寄存器。
		/// 	@note 其实就是普通的整型，只要是整型都可以。寄存器也可以强制转换成整型的指针，
		/// 	解引用后传进来。
		///
		/// @param bit_index 要复位的位的索引。
		///
		template <typename RegisterType, std::enable_if_t<std::is_integral_v<RegisterType>, int> = 0>
		constexpr void ResetBit(RegisterType &reg, int bit_index)
		{
			CheckBitIndex<RegisterType>(bit_index);
			reg &= ~Bit(bit_index);
		}

		template <typename RegisterType, std::enable_if_t<std::is_integral_v<RegisterType>, int> = 0>
		constexpr void ResetBits(RegisterType &reg, int begin, int end)
		{
			CheckBitRange<RegisterType>(begin, end);
			reg &= ~BitMask(begin, end);
		}

		///
		/// @brief 读取指定位的值。
		///
		/// @param reg 寄存器。
		/// @param bit_index 要读取的位的索引。
		///
		/// @return
		///
		template <typename RegisterType, std::enable_if_t<std::is_integral_v<RegisterType>, int> = 0>
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
		template <typename RegisterType, std::enable_if_t<std::is_integral_v<RegisterType>, int> = 0>
		constexpr RegisterType ReadBits(RegisterType const &reg, int begin, int end)
		{
			CheckBitRange<RegisterType>(begin, end);
			RegisterType ret = reg & BitMask(begin, end);
			ret >>= begin;
			return ret;
		}

		///
		/// @brief 将值写入寄存器指定的位范围。
		///
		/// @param reg 寄存器。
		/// @param begin 位范围起始。闭端点。
		/// @param end 位范围结束。开端点。
		/// @param value 要写入 reg 的指定范围内的值。
		/// @return
		///
		template <typename RegisterType, std::enable_if_t<std::is_integral_v<RegisterType>, int> = 0>
		constexpr void WriteBits(RegisterType &reg, int begin, int end, uint64_t value)
		{
			CheckBitRange<RegisterType>(begin, end);

			// 将值移位，与要写入的寄存器位置对齐。
			value <<= begin;

			// 读取出范围内的位，其它部分的位丢弃（让它们是 0.）
			value = ReadBits(value, begin, end);
			ResetBits(reg, begin, end);
			reg |= value;
		}

	} // namespace bit
} // namespace base

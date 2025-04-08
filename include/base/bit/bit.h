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
		///
		/// @brief 从最高位开始数，有多少个连续的 0.
		///
		/// @param num
		/// @return constexpr int
		///
		constexpr int HighZeroCount(uint8_t num)
		{
			return std::countl_zero(num);
		}

		///
		/// @brief 从最高位开始数，有多少个连续的 0.
		///
		/// @param num
		/// @return constexpr int
		///
		constexpr int HighZeroCount(uint16_t num)
		{
			return std::countl_zero(num);
		}

		///
		/// @brief 从最高位开始数，有多少个连续的 0.
		///
		/// @param num
		/// @return constexpr int
		///
		constexpr int HighZeroCount(uint32_t num)
		{
			return std::countl_zero(num);
		}

		///
		/// @brief 从最高位开始数，有多少个连续的 0.
		///
		/// @param num
		/// @return constexpr int
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
		/// @return constexpr int
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
		/// @return constexpr int
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
		/// @return constexpr int
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
		/// @return constexpr int
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
		/// @return constexpr uint8_t
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
		/// @return constexpr uint16_t
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
		/// @return constexpr uint32_t
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
		/// @return constexpr uint64_t
		///
		constexpr uint64_t AlignToLeft(uint64_t num)
		{
			return num << HighZeroCount(num);
		}

		///
		/// @brief 获取一个只有 bit_index 指定的位为 1, 其他位都为 0 的掩码。
		///
		/// @param bit_index
		/// @return constexpr uint64_t
		///
		constexpr uint64_t Bit(int bit_index)
		{
			if (bit_index < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "索引溢出。"};
			}

			if (bit_index >= 64)
			{
				throw std::invalid_argument{CODE_POS_STR + "索引溢出。"};
			}

			return 0b1 << bit_index;
		}

		///
		/// @brief 获取位掩码。其中指定范围内的位为 1, 其他位为 0.
		/// 	@note 是一个左闭右开区间。
		///
		/// @param begin 起始索引。左端点是闭的。
		/// @param end 结束索引。右端点是开的。
		///
		/// @return constexpr uint64_t
		///
		constexpr uint64_t BitMask(int begin, int end)
		{
			uint64_t ret = 0;
			if (begin < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "索引溢出。"};
			}

			if (end > 64)
			{
				throw std::invalid_argument{CODE_POS_STR + "索引溢出。"};
			}

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
			reg |= Bit(bit_index);
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
			reg &= ~Bit(bit_index);
		}

		///
		/// @brief 读取指定位的值。
		///
		/// @param reg 寄存器。
		/// @param bit_index 要读取的位的索引。
		///
		/// @return bool
		///
		template <typename RegisterType, std::enable_if_t<std::is_integral_v<RegisterType>, int> = 0>
		constexpr bool ReadBit(RegisterType const &reg, int bit_index)
		{
			return reg & Bit(bit_index);
		}

	} // namespace bit
} // namespace base

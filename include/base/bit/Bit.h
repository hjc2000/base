#pragma once
#include <base/define.h>
#include <bit>
#include <stdint.h>

namespace base
{
	/// @brief 静态类。提供一些位操作的函数。
	class Bit final
	{
	private:
		Bit() = delete;

	public:
		/// @brief 从最高位开始数，有多少个连续的 0.
		/// @param num
		/// @return
		static_function constexpr int HighZeroCount(uint8_t num)
		{
			return std::countl_zero(num);
		}

		/// @brief 从最高位开始数，有多少个连续的 0.
		/// @param num
		/// @return
		static_function constexpr int HighZeroCount(uint16_t num)
		{
			return std::countl_zero(num);
		}

		/// @brief 从最高位开始数，有多少个连续的 0.
		/// @param num
		/// @return
		static_function constexpr int HighZeroCount(uint32_t num)
		{
			return std::countl_zero(num);
		}

		/// @brief 从最高位开始数，有多少个连续的 0.
		/// @param num
		/// @return
		static_function constexpr int HighZeroCount(uint64_t num)
		{
			return std::countl_zero(num);
		}

		/// @brief 最高位的 1 的索引。
		/// @note 例如 0x1 的 bit0 是最高位的 1，于是返回 0.
		///
		/// @param num
		/// @return
		static_function constexpr int HighestOneBitIndex(uint8_t num)
		{
			int count = HighZeroCount(num);
			return 8 - count - 1;
		}

		/// @brief 最高位的 1 的索引。
		/// @note 例如 0x1 的 bit0 是最高位的 1，于是返回 0.
		///
		/// @param num
		/// @return
		static_function constexpr int HighestOneBitIndex(uint16_t num)
		{
			int count = HighZeroCount(num);
			return 16 - count - 1;
		}

		/// @brief 最高位的 1 的索引。
		/// @note 例如 0x1 的 bit0 是最高位的 1，于是返回 0.
		///
		/// @param num
		/// @return
		static_function constexpr int HighestOneBitIndex(uint32_t num)
		{
			int count = HighZeroCount(num);
			return 32 - count - 1;
		}

		/// @brief 最高位的 1 的索引。
		/// @note 例如 0x1 的 bit0 是最高位的 1，于是返回 0.
		///
		/// @param num
		/// @return
		static_function constexpr int HighestOneBitIndex(uint64_t num)
		{
			int count = HighZeroCount(num);
			return 64 - count - 1;
		}

		/// @brief 将 num 进行左对齐。
		/// @note 即将 num 进行左移位，使最高位的 1 位于最高有效位，即去除所有的前导 0.
		///
		/// @param num
		/// @return
		static_function constexpr uint8_t AlignToLeft(uint8_t num)
		{
			return num << HighZeroCount(num);
		}

		/// @brief 将 num 进行左对齐。
		/// @note 即将 num 进行左移位，使最高位的 1 位于最高有效位，即去除所有的前导 0.
		///
		/// @param num
		/// @return
		static_function constexpr uint16_t AlignToLeft(uint16_t num)
		{
			return num << HighZeroCount(num);
		}

		/// @brief 将 num 进行左对齐。
		/// @note 即将 num 进行左移位，使最高位的 1 位于最高有效位，即去除所有的前导 0.
		///
		/// @param num
		/// @return
		static_function constexpr uint32_t AlignToLeft(uint32_t num)
		{
			return num << HighZeroCount(num);
		}

		/// @brief 将 num 进行左对齐。
		/// @note 即将 num 进行左移位，使最高位的 1 位于最高有效位，即去除所有的前导 0.
		///
		/// @param num
		/// @return
		static_function constexpr uint64_t AlignToLeft(uint64_t num)
		{
			return num << HighZeroCount(num);
		}
	};
} // namespace base

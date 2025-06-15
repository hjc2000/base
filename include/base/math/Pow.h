#pragma once
#include "boost/multiprecision/cpp_int.hpp" // IWYU pragma: keep
#include <cmath>
#include <cstdint>

namespace base
{
	///
	/// @brief 求幂。
	///
	/// @param x 底数
	/// @param y 指数
	/// @return
	///
	constexpr uint64_t UIntPow(uint64_t x, uint64_t y)
	{
		if (x == 0)
		{
			if (y == 0)
			{
				// 特殊情况，定义 0 ^ 0 = 1.
				return 1;
			}

			// 其他情况，0 的正整数次幂都为 0.
			return 0;
		}

		uint64_t result = 1;
		for (uint64_t i = 0; i < y; i++)
		{
			result *= x;
		}

		return result;
	}

	///
	/// @brief 求幂。
	///
	/// @note 只能求指数 >= 0 的幂。
	///
	/// @param x 底数
	/// @param y 指数
	/// @return
	///
	boost::multiprecision::cpp_int BigIntPow(boost::multiprecision::cpp_int x,
											 boost::multiprecision::cpp_int y);
} // namespace base

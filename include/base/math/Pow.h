#pragma once
#include <cstdint>

namespace base
{
	/**
	 * @brief 求幂。
	 *
	 * @note 只能求指数 >=0 的幂。
	 *
	 * @param x 底数
	 * @param y 指数
	 * @return constexpr int64_t
	 */
	constexpr int64_t IntPow(int64_t x, int64_t y)
	{
		if (x == 0)
		{
			return 0;
		}

		if (y < 0)
		{
			return 0;
		}

		int64_t result = 1;
		for (int i = 0; i < y; i++)
		{
			result *= x;
		}

		return result;
	}
} // namespace base

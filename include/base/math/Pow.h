#pragma once
#include "base/string/define.h"
#include "boost/multiprecision/cpp_int.hpp" // IWYU pragma: keep
#include <cstdint>
#include <stdexcept>

namespace base
{
	///
	/// @brief 求幂。
	///
	/// @note 只能求指数 >= 0 的幂。
	///
	/// @param x 底数
	/// @param y 指数
	/// @return constexpr int64_t
	///
	constexpr int64_t IntPow(int64_t x, int64_t y)
	{
		if (x == 0)
		{
			throw std::invalid_argument{CODE_POS_STR + "x 不能等于 0."};
		}

		if (y < 0)
		{
			throw std::invalid_argument{CODE_POS_STR + "y 不能小于 0."};
		}

		int64_t result = 1;
		for (int64_t i = 0; i < y; i++)
		{
			result *= x;
		}

		return result;
	}

	///
	/// @brief 求幂。
	///
	/// @param x 底数
	/// @param y 指数
	/// @return constexpr int64_t
	///
	constexpr uint64_t UIntPow(uint64_t x, uint64_t y)
	{
		if (x == 0)
		{
			throw std::invalid_argument{CODE_POS_STR + "x 不能等于 0."};
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
	/// @return constexpr boost::multiprecision::cpp_int
	///
	boost::multiprecision::cpp_int BigIntPow(boost::multiprecision::cpp_int x,
											 boost::multiprecision::cpp_int y);
} // namespace base

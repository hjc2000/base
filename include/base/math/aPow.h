#pragma once
#include "base/string/define.h"
#include "boost/multiprecision/cpp_int.hpp" // IWYU pragma: keep
#include <cstdint>
#include <stdexcept>
#include <type_traits>

namespace base
{
	///
	/// @brief 针对有符号整型的幂函数模板。
	///
	/// @param x
	/// @param y
	/// @return
	///
	template <typename T>
		requires(std::is_signed_v<T>)
	constexpr T pow(T x, T y)
	{
		if (y < 0)
		{
			throw std::invalid_argument{CODE_POS_STR + "y 不能 < 0."};
		}

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

		T result = 1;
		T base_number = x;
		T exponent = y;
		while (true)
		{
			if (exponent % 2 != 0)
			{
				result *= base_number;
				exponent -= 1;
				continue;
			}

			// 指数是偶数，则底数平方后，指数可以除以 2. 一下子就将指数减小很多。
			base_number *= base_number;
			exponent /= 2;
			if (exponent == 0)
			{
				break;
			}
		}

		return result;
	}

	///
	/// @brief 针对无符号整型的幂函数模板。
	///
	/// @param x
	/// @param y
	/// @return
	///
	template <typename T>
		requires(std::is_unsigned_v<T>)
	constexpr T pow(T x, T y)
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

		T result = 1;
		T base_number = x;
		T exponent = y;
		while (true)
		{
			if (exponent % 2 != 0)
			{
				result *= base_number;
				exponent -= 1;
				continue;
			}

			// 指数是偶数，则底数平方后，指数可以除以 2. 一下子就将指数减小很多。
			base_number *= base_number;
			exponent /= 2;
			if (exponent == 0)
			{
				break;
			}
		}

		return result;
	}

	///
	/// @brief 针对 boost::multiprecision::cpp_int 的幂函数模板。
	///
	///
	template <typename T>
		requires(std::is_same_v<T, boost::multiprecision::cpp_int>)
	constexpr T pow(T x, T y)
	{
		if (y < 0)
		{
			throw std::invalid_argument{CODE_POS_STR + "y 不能 < 0."};
		}

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

		T result = 1;
		T base_number = x;
		T exponent = y;
		while (true)
		{
			if (exponent % 2 != 0)
			{
				result *= base_number;
				exponent -= 1;
				continue;
			}

			// 指数是偶数，则底数平方后，指数可以除以 2. 一下子就将指数减小很多。
			base_number *= base_number;
			exponent /= 2;
			if (exponent == 0)
			{
				break;
			}
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
	constexpr int64_t IntPow(int64_t x, int64_t y)
	{
		if (y < 0)
		{
			throw std::invalid_argument{CODE_POS_STR + "y 不能 < 0."};
		}

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

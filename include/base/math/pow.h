#pragma once
#include "base/math/math.h"
#include "base/string/define.h"
#include "boost/multiprecision/cpp_int.hpp" // IWYU pragma: keep
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
	/// @brief 针对 base::BigInteger 的幂函数模板。
	///
	///
	template <typename T>
		requires(std::is_same_v<T, base::BigInteger>)
	constexpr T pow(T const &x, T const &y)
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

} // namespace base

#pragma once
#include "base/string/define.h"
#include <cstdint>
#include <stdexcept>
#include <type_traits>

namespace base
{
	template <typename T>
		requires(std::is_same_v<T, double>)
	constexpr int64_t floor(T value) noexcept
	{
		return static_cast<int64_t>(value);
	}

	template <typename T>
		requires(std::is_same_v<T, float>)
	constexpr int64_t floor(T value) noexcept
	{
		return static_cast<int64_t>(value);
	}

	template <typename T>
		requires(std::is_same_v<T, double>)
	constexpr int64_t ceil(T value) noexcept
	{
		int64_t int_part = static_cast<int64_t>(value);
		double fractional_part = value - static_cast<double>(int_part);
		if (fractional_part == 0.0)
		{
			return int_part;
		}

		return int_part + 1;
	}

	template <typename T>
		requires(std::is_same_v<T, float>)
	constexpr int64_t ceil(T value) noexcept
	{
		int64_t int_part = static_cast<int64_t>(value);
		float fractional_part = value - static_cast<float>(int_part);
		if (fractional_part == 0.0f)
		{
			return int_part;
		}

		return int_part + 1;
	}

	///
	/// @brief 求绝对值。
	///
	/// @param value
	/// @return
	///
	template <typename T>
		requires(std::is_integral_v<T> || std::is_floating_point_v<T>)
	constexpr T abs(T const &value) noexcept
	{
		if (value < T{})
		{
			return -value;
		}

		return value;
	}

	///
	/// @brief 降低分辨率。
	///
	/// @return 降低分辨率后的值。
	///
	template <typename T>
		requires(std::is_integral_v<T>)
	constexpr T reduce_resolution(T value, T resolution) noexcept
	{
		return value / resolution * resolution;
	}

	///
	/// @brief 降低分辨率。
	///
	/// @return 降低分辨率后的值。
	///
	template <typename T>
		requires(std::is_floating_point_v<T>)
	constexpr T reduce_resolution(T value, T resolution) noexcept
	{
		return base::floor(value / resolution) * resolution;
	}

	///
	/// @brief 求最大公约数。
	///
	template <typename T>
		requires(std::is_integral_v<T>)
	constexpr T gcd(T a, T b) noexcept
	{
		{
			// 最大公因数 gcd 可以乘上一个整数得到 a, 也可以乘上一个整数得到 b.
			//
			// 当 a, b 其中一个为 0, 另一个不为 0 时，gcd 为不为 0 的那个的绝对值。
			// 假设 a = 0, b != 0, 则此时 gcd = b, 满足
			// gcd * 0 = a
			// gcd * 1 = b
			// 所以 gcd 可以称得上是最大公因数。
			//
			// 当 a, b 都为 0 时，gcd = 0, 满足
			// gcd * 0 = a
			// gcd * 0 = b
			// 所以 gcd 可以称得上是最大公因数。

			if (a == 0)
			{
				return base::abs(b);
			}

			if (b == 0)
			{
				return base::abs(a);
			}

			// 没必要写出
			//
			// 	if (a == 0 && b == 0)
			// 	{
			// 		return 0;
			// 	}
			//
			// 因为前面的 2 个 if 已经能处理这种情况了。
		}

		a = base::abs(a);
		b = base::abs(b);

		while (true)
		{
			T mod = a % b;
			if (mod == 0)
			{
				return b;
			}

			a = b;
			b = mod;
		}
	}

	///
	/// @brief 求最小公倍数。
	///
	template <typename T>
		requires(std::is_integral_v<T>)
	constexpr T lcm(T a, T b) noexcept
	{
		T mul = base::abs(a * b);
		if (mul == 0)
		{
			// 最大公倍数 lcm 满足 a 乘上一个整数等于 lcm, b 乘上一个整数等于 lcm.
			//
			// 当 a, b 其中一个为 0, 时，想要让 a, b 乘上整数都能等于 lcm, 因为 0
			// 乘上什么都等于 0, 所以只能让 lcm 等于 0, 然后
			// a * 0 = lcm
			// b * 0 = lcm
			return 0;
		}

		T gcd = base::gcd(a, b);

		// 如果最大公因数是其中的一个数，则另一个数一定是它们的最小公倍数。
		if (gcd == a)
		{
			return b;
		}

		if (gcd == b)
		{
			return a;
		}

		return mul / gcd;
	}

	///
	/// @brief 阶乘。
	///
	/// @param num
	///
	/// @return
	///
	template <typename T>
		requires(std::is_signed_v<T>)
	constexpr T factorial(T num)
	{
		if (num < 0)
		{
			throw std::invalid_argument{CODE_POS_STR + "负数没有定义阶乘。"};
		}

		if (num == 0)
		{
			return 1;
		}

		if (num == 1)
		{
			return 1;
		}

		T result = 1;
		for (T i = 1; i <= num; i++)
		{
			result *= i;
		}

		return result;
	}

	///
	/// @brief 阶乘。
	///
	/// @param num
	///
	/// @return
	///
	template <typename T>
		requires(std::is_unsigned_v<T>)
	constexpr T factorial(T num)
	{
		if (num == 0)
		{
			return 1;
		}

		if (num == 1)
		{
			return 1;
		}

		T result = 1;
		for (T i = 1; i <= num; i++)
		{
			result *= i;
		}

		return result;
	}

} // namespace base

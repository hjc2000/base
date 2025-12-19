#pragma once
#include "base/math/math.h"
#include "base/string/define.h"
#include "boost/multiprecision/cpp_int.hpp" // IWYU pragma: keep
#include <cstdint>
#include <stdexcept>
#include <type_traits>

namespace base
{
	using BigInteger = boost::multiprecision::cpp_int;
	using Int128 = boost::multiprecision::int128_t;

	template <typename T>
	concept is_big_integer = requires() {
		requires(std::is_same_v<T, base::BigInteger> ||
				 std::is_same_v<T, base::Int128>);
	};

	///
	/// @brief 将大整型转换为字符串。
	///
	/// @param value
	/// @return
	///
	template <typename T>
		requires(base::is_big_integer<T>)
	constexpr std::string to_string(T const &value)
	{
		T temp = value;
		bool is_negative = temp < 0;
		std::string ret;
		if (temp == 0)
		{
			return "0";
		}

		if (temp < 0)
		{
			temp = -temp;
		}

		while (temp > 0)
		{
			uint8_t num = static_cast<uint8_t>(temp % 10);
			ret = std::to_string(num) + ret;
			temp /= 10;
		}

		if (is_negative)
		{
			ret = '-' + ret;
		}

		return ret;
	}

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
	constexpr T abs(T value) noexcept
	{
		if (value < T{})
		{
			return -value;
		}

		return value;
	}

	///
	/// @brief 求绝对值。
	///
	/// @param value
	/// @return
	///
	template <typename T>
		requires(base::is_big_integer<T>)
	constexpr T abs(T const &value)
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
	/// @brief 求最大公约数。
	///
	template <typename T>
		requires(base::is_big_integer<T>)
	constexpr T gcd(T const &a, T const &b)
	{
		return boost::multiprecision::gcd(a, b);
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
	/// @brief 求最小公倍数。
	///
	template <typename T>
		requires(base::is_big_integer<T>)
	constexpr T lcm(T const &a, T const &b)
	{
		return boost::multiprecision::lcm(a, b);
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

	///
	/// @brief 阶乘。
	///
	/// @param num
	///
	/// @return
	///
	template <typename T>
		requires(base::is_big_integer<T>)
	constexpr T factorial(T const &num)
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
	/// @brief 幂函数。
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
	/// @brief 幂函数。
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
	/// @brief 幂函数。
	///
	///
	template <typename T>
		requires(base::is_big_integer<T>)
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

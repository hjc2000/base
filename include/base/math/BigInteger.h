#pragma once
#include "base/string/define.h"
#include "boost/multiprecision/cpp_int.hpp" // IWYU pragma: keep
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
	/// @brief 求最大公约数。
	///
	template <typename T>
		requires(base::is_big_integer<T>)
	constexpr T gcd(T a, T b)
	{
		return boost::multiprecision::gcd(a, b);
	}

	///
	/// @brief 求最小公倍数。
	///
	template <typename T>
		requires(base::is_big_integer<T>)
	constexpr T lcm(T a, T b)
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

} // namespace base

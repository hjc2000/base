#pragma once
#include "boost/multiprecision/cpp_int.hpp" // IWYU pragma: keep

namespace base
{
	using BigInteger = boost::multiprecision::cpp_int;

	///
	/// @brief 将大整型转换为字符串。
	///
	/// @param value
	/// @return
	///
	std::string to_string(base::BigInteger const &value);

	///
	/// @brief 求绝对值。
	///
	/// @param value
	/// @return
	///
	template <typename T>
		requires(std::is_same_v<T, base::BigInteger>)
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
		requires(std::is_same_v<T, base::BigInteger>)
	constexpr T gcd(T a, T b)
	{
		return boost::multiprecision::gcd(a, b);
	}

	///
	/// @brief 求最小公倍数。
	///
	template <typename T>
		requires(std::is_same_v<T, base::BigInteger>)
	constexpr T lcm(T a, T b)
	{
		return boost::multiprecision::lcm(a, b);
	}

} // namespace base

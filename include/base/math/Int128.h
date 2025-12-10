#pragma once
#include "boost/multiprecision/cpp_int.hpp" // IWYU pragma: keep
#include <type_traits>

namespace base
{
	using Int128 = boost::multiprecision::int128_t;

	///
	/// @brief 求绝对值。
	///
	/// @param value
	/// @return
	///
	template <typename T>
		requires(std::is_same_v<T, base::Int128>)
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
		requires(std::is_same_v<T, base::Int128>)
	constexpr T gcd(T a, T b)
	{
		return boost::multiprecision::gcd(a, b);
	}

	///
	/// @brief 求最小公倍数。
	///
	template <typename T>
		requires(std::is_same_v<T, base::Int128>)
	constexpr T lcm(T a, T b)
	{
		return boost::multiprecision::lcm(a, b);
	}

} // namespace base

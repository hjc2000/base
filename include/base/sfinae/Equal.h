#pragma once
#include <type_traits>

namespace base
{
	///
	/// @brief 概念：T 具有比较运算符。
	///
	/// @param a
	/// @param b
	/// @return
	///
	template <typename T>
	concept has_equal_operator = requires(T a, T b) {
		requires(std::is_same_v<decltype(a == b), bool>);
	};

	///
	/// @brief 如果一个类型有定义相等运算符，则使用相等运算符进行比较。
	///
	/// @param lhs
	/// @param rhs
	/// @return
	///
	template <typename T>
		requires(base::has_equal_operator<T>)
	inline constexpr bool Equal(T const &lhs, T const &rhs)
	{
		return lhs == rhs;
	}

	///
	/// @brief 如果一个类型没有定义相等运算符，则将相等逻辑定义为比较指针。
	///
	/// @param lhs
	/// @param rhs
	/// @return
	///
	template <typename T>
		requires(!base::has_equal_operator<T>)
	inline constexpr bool Equal(T const &lhs, T const &rhs)
	{
		return &lhs == &rhs;
	}

} // namespace base

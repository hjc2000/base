#pragma once
#include <type_traits>

namespace base
{
	template <typename T, typename = void>
	struct has_equal_operator :
		std::false_type
	{
	};

	template <typename T>
	struct has_equal_operator<T, std::void_t<decltype(std::declval<T>() == std::declval<T>())>> :
		std::true_type
	{
	};

	///
	/// @brief 如果一个类型有定义相等运算符，则使用相等运算符进行比较。
	///
	/// @param lhs
	/// @param rhs
	/// @return std::enable_if_t<base::has_equal_operator<T>::value, bool>
	///
	template <typename T>
	inline constexpr auto Equal(T const &lhs, T const &rhs)
		-> std::enable_if_t<base::has_equal_operator<T>::value, bool>
	{
		return lhs == rhs;
	}

	///
	/// @brief 如果一个类型没有定义相等运算符，则将相等逻辑定义为比较指针。
	///
	/// @param lhs
	/// @param rhs
	/// @return std::enable_if_t<!base::has_equal_operator<T>::value, bool>
	///
	template <typename T>
	inline constexpr auto Equal(T const &lhs, T const &rhs)
		-> std::enable_if_t<!base::has_equal_operator<T>::value, bool>
	{
		return &lhs == &rhs;
	}
} // namespace base

#pragma once
#include <type_traits>

namespace base
{
	// Step 1: Define a detector for the == operator
	template <typename T, typename = void>
	struct has_equal_operator : std::false_type
	{
	};

	template <typename T>
	struct has_equal_operator<T, std::void_t<decltype(std::declval<T>() == std::declval<T>())>> :
		std::true_type
	{
	};
} // namespace base

/// @brief 如果一个类型没有定义相等运算符，则将相等逻辑定义为比较指针。
/// @tparam T
/// @param lhs
/// @param rhs
/// @return
template <typename T>
inline auto operator==(T const &lhs, T const &rhs)
	-> std::enable_if_t<!base::has_equal_operator<T>::value, bool>
{
	return &lhs == &rhs;
}

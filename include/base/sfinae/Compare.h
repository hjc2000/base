#pragma once
#include <type_traits>

namespace base
{
	///
	/// @brief 概念：具有相等运算符。
	///
	template <typename TLeft, typename TRight>
	concept has_equal_operator = requires(TLeft a, TRight b) {
		requires(std::is_same_v<decltype(a == b), bool>);
	};

	///
	/// @brief 概念：具有小于运算符。
	///
	template <typename TLeft, typename TRight>
	concept has_less_than_operator = requires(TLeft a, TRight b) {
		requires(std::is_same_v<decltype(a < b), bool>);
	};

	///
	/// @brief 概念：具有大于运算符。
	///
	template <typename TLeft, typename TRight>
	concept has_greater_than_operator = requires(TLeft a, TRight b) {
		requires(std::is_same_v<decltype(a > b), bool>);
	};

	///
	/// @brief 概念：具有小于等于运算符。
	///
	template <typename TLeft, typename TRight>
	concept has_less_than_or_equal_operator = requires(TLeft a, TRight b) {
		requires(std::is_same_v<decltype(a <= b), bool>);
	};

	///
	/// @brief 概念：具有大于等于运算符。
	///
	template <typename TLeft, typename TRight>
	concept has_greater_than_or_equal_operator = requires(TLeft a, TRight b) {
		requires(std::is_same_v<decltype(a >= b), bool>);
	};

	///
	/// @brief 概念：具有所有的比较运算符。
	///
	template <typename TLeft, typename TRight>
	concept has_all_compare_operators = requires(TLeft a, TRight b) {
		requires(base::has_equal_operator<TLeft, TRight> &&
				 base::has_less_than_operator<TLeft, TRight> &&
				 base::has_greater_than_operator<TLeft, TRight> &&
				 base::has_less_than_or_equal_operator<TLeft, TRight> &&
				 base::has_greater_than_or_equal_operator<TLeft, TRight>);
	};

} // namespace base

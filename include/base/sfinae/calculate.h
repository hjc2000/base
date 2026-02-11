#pragma once
#include <type_traits>

namespace base
{
	///
	/// @brief 概念：有加法运算符。
	///
	/// @param a
	/// @param b
	/// @return
	///
	template <typename ReturnType, typename TLeft, typename TRight>
	concept has_add_operator = requires(TLeft a, TRight b) {
		requires(std::is_same_v<decltype(a + b), ReturnType>);
	};

	///
	/// @brief 概念：有减法运算符。
	///
	/// @param a
	/// @param b
	/// @return
	///
	template <typename ReturnType, typename TLeft, typename TRight>
	concept has_minus_operator = requires(TLeft a, TRight b) {
		requires(std::is_same_v<decltype(a - b), ReturnType>);
	};

	///
	/// @brief 概念：有乘法运算符。
	///
	/// @param a
	/// @param b
	/// @return
	///
	template <typename ReturnType, typename TLeft, typename TRight>
	concept has_multiplication_operator = requires(TLeft a, TRight b) {
		requires(std::is_same_v<decltype(a * b), ReturnType>);
	};

	///
	/// @brief 概念：有除法运算符。
	///
	/// @param a
	/// @param b
	/// @return
	///
	template <typename ReturnType, typename TLeft, typename TRight>
	concept has_div_operator = requires(TLeft a, TRight b) {
		requires(std::is_same_v<decltype(a / b), ReturnType>);
	};

	///
	/// @brief 概念：有取余运算符。
	///
	/// @param a
	/// @param b
	/// @return
	///
	template <typename ReturnType, typename TLeft, typename TRight>
	concept has_mod_operator = requires(TLeft a, TRight b) {
		requires(std::is_same_v<decltype(a % b), ReturnType>);
	};

} // namespace base

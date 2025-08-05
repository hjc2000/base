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

} // namespace base

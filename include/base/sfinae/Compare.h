#pragma once
#include "base/sfinae/Equal.h" // IWYU pragma: export
#include <type_traits>

namespace base
{
	template <typename T, typename = void>
	concept has_less_than_operator = requires(T a, T b) {
		requires(std::is_same_v<decltype(a < b), bool>);
	};

	template <typename T, typename = void>
	concept has_greater_than_operator = requires(T a, T b) {
		requires(std::is_same_v<decltype(a > b), bool>);
	};

	template <typename T, typename = void>
	concept has_less_than_or_equal_operator = requires(T a, T b) {
		requires(std::is_same_v<decltype(a <= b), bool>);
	};

	template <typename T, typename = void>
	concept has_greater_than_or_equal_operator = requires(T a, T b) {
		requires(std::is_same_v<decltype(a >= b), bool>);
	};

} // namespace base

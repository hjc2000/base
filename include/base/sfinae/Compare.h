#pragma once
#include "base/sfinae/Equal.h" // IWYU pragma: export
#include "base/string/define.h"
#include <stdexcept>
#include <type_traits>

namespace base
{
	/* #region 小于 */

	template <typename T, typename = void>
	concept has_less_than_operator = requires(T a, T b) {
		requires(std::is_same_v<decltype(a < b), bool>);
	};

	template <typename T>
		requires(base::has_less_than_operator<T>)
	inline constexpr bool LessThan(T const &lhs, T const &rhs)
	{
		return lhs < rhs;
	}

	template <typename T>
		requires(!base::has_less_than_operator<T>)
	inline constexpr bool LessThan(T const &lhs, T const &rhs)
	{
		throw std::runtime_error{CODE_POS_STR + "请先实现 < 运算符。"};
		return false;
	}

	/* #endregion */

	/* #region 大于 */

	template <typename T, typename = void>
	concept has_greater_than_operator = requires(T a, T b) {
		requires(std::is_same_v<decltype(a > b), bool>);
	};

	template <typename T>
		requires(base::has_less_than_operator<T>)
	inline constexpr bool GreaterThan(T const &lhs, T const &rhs)
	{
		return lhs > rhs;
	}

	template <typename T>
		requires(!base::has_less_than_operator<T>)
	inline constexpr bool GreaterThan(T const &lhs, T const &rhs)
	{
		throw std::runtime_error{CODE_POS_STR + "请先实现 > 运算符。"};
		return false;
	}

	/* #endregion */

	/* #region 小于等于。 */

	template <typename T, typename = void>
	concept has_less_than_or_equal_operator = requires(T a, T b) {
		requires(std::is_same_v<decltype(a <= b), bool>);
	};

	template <typename T>
		requires(base::has_less_than_or_equal_operator<T>)
	inline constexpr bool LessThanOrEqual(T const &lhs, T const &rhs)
	{
		return lhs <= rhs;
	}

	template <typename T>
		requires(!base::has_less_than_or_equal_operator<T>)
	inline constexpr bool LessThanOrEqual(T const &lhs, T const &rhs)
	{
		throw std::runtime_error{CODE_POS_STR + "请先实现 <= 运算符。"};
		return false;
	}

	/* #endregion */

	/* #region 大于等于。 */

	template <typename T, typename = void>
	concept has_greater_than_or_equal_operator = requires(T a, T b) {
		requires(std::is_same_v<decltype(a >= b), bool>);
	};

	template <typename T>
		requires(base::has_greater_than_or_equal_operator<T>)
	inline constexpr bool GreaterThanOrEqual(T const &lhs, T const &rhs)
	{
		return lhs >= rhs;
	}

	template <typename T>
		requires(!base::has_greater_than_or_equal_operator<T>)
	inline constexpr bool GreaterThanOrEqual(T const &lhs, T const &rhs)
	{
		throw std::runtime_error{CODE_POS_STR + "请先实现 >= 运算符。"};
		return false;
	}

	/* #endregion */

} // namespace base

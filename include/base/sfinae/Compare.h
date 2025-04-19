#pragma once
#include "base/sfinae/Equal.h" // IWYU pragma: export
#include "base/string/define.h"
#include <concepts>
#include <stdexcept>

namespace base
{
	/* #region 小于 */

	template <typename T, typename = void>
	concept has_less_than_operator = requires(T a, T b) {
		requires std::same_as<decltype(a < b), bool>;
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
		requires std::same_as<decltype(a > b), bool>;
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
		requires std::same_as<decltype(a <= b), bool>;
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
		requires std::same_as<decltype(a >= b), bool>;
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

	///
	/// @brief 比较。
	///
	/// @param left
	/// @param right
	///
	/// @return 如果 left 小于 right，则返回 -1，如果 left 大于 right ，则返回 1，
	/// 其他情况视为等于，返回 0.
	///
	template <typename T>
	int Compare(T const &left, T const &right)
	{
		if (base::LessThan(left, right))
		{
			return -1;
		}

		if (base::GreaterThan(left, right))
		{
			return 1;
		}

		return 0;
	}

} // namespace base

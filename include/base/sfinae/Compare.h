#pragma once
#include "base/sfinae/Equal.h" // IWYU pragma: export
#include "base/string/define.h"
#include <stdexcept>
#include <type_traits>

/**
 * @brief 小于
 *
 */
namespace base
{
	template <typename T, typename = void>
	struct has_less_than_operator :
		std::false_type
	{
	};

	template <typename T>
	struct has_less_than_operator<T, std::void_t<decltype(std::declval<T>() < std::declval<T>())>> :
		std::true_type
	{
	};

	template <typename T>
	inline constexpr auto LessThan(T const &lhs, T const &rhs)
		-> std::enable_if_t<base::has_less_than_operator<T>::value, bool>
	{
		return lhs < rhs;
	}

	template <typename T>
	inline constexpr auto LessThan(T const &lhs, T const &rhs)
		-> std::enable_if_t<!base::has_less_than_operator<T>::value, bool>
	{
		throw std::runtime_error{CODE_POS_STR + "请先实现 < 运算符。"};
	}
} // namespace base

/**
 * @brief 大于。
 *
 */
namespace base
{
	template <typename T, typename = void>
	struct has_greater_than_operator :
		std::false_type
	{
	};

	template <typename T>
	struct has_greater_than_operator<T, std::void_t<decltype(std::declval<T>() > std::declval<T>())>> :
		std::true_type
	{
	};

	template <typename T>
	inline constexpr auto GreaterThan(T const &lhs, T const &rhs)
		-> std::enable_if_t<base::has_greater_than_operator<T>::value, bool>
	{
		return lhs > rhs;
	}

	template <typename T>
	inline constexpr auto GreaterThan(T const &lhs, T const &rhs)
		-> std::enable_if_t<!base::has_greater_than_operator<T>::value, bool>
	{
		throw std::runtime_error{CODE_POS_STR + "请先实现 > 运算符。"};
	}
} // namespace base

/**
 * @brief 小于等于。
 *
 */
namespace base
{
	template <typename T, typename = void>
	struct has_less_than_or_equal_operator :
		std::false_type
	{
	};

	template <typename T>
	struct has_less_than_or_equal_operator<T, std::void_t<decltype(std::declval<T>() <= std::declval<T>())>> :
		std::true_type
	{
	};

	template <typename T>
	inline constexpr auto GreaterThanOrEqual(T const &lhs, T const &rhs)
		-> std::enable_if_t<base::has_less_than_or_equal_operator<T>::value, bool>
	{
		return lhs <= rhs;
	}

	template <typename T>
	inline constexpr auto GreaterThanOrEqual(T const &lhs, T const &rhs)
		-> std::enable_if_t<!base::has_less_than_or_equal_operator<T>::value, bool>
	{
		throw std::runtime_error{CODE_POS_STR + "请先实现 <= 运算符。"};
	}
} // namespace base

/**
 * @brief 大于等于。
 *
 */
namespace base
{
	template <typename T, typename = void>
	struct has_greater_than_or_equal_operator :
		std::false_type
	{
	};

	template <typename T>
	struct has_greater_than_or_equal_operator<T, std::void_t<decltype(std::declval<T>() >= std::declval<T>())>> :
		std::true_type
	{
	};

	template <typename T>
	inline constexpr auto GreaterThanOrEqual(T const &lhs, T const &rhs)
		-> std::enable_if_t<base::has_greater_than_or_equal_operator<T>::value, bool>
	{
		return lhs >= rhs;
	}

	template <typename T>
	inline constexpr auto GreaterThanOrEqual(T const &lhs, T const &rhs)
		-> std::enable_if_t<!base::has_greater_than_or_equal_operator<T>::value, bool>
	{
		throw std::runtime_error{CODE_POS_STR + "请先实现 >= 运算符。"};
	}
} // namespace base

namespace base
{
	/**
	 * @brief 比较。
	 *
	 * @tparam T
	 * @param left
	 * @param right
	 * @return int 如果 left 小于 right，则返回 -1，如果 left 大于 right ，则返回 1，
	 * 其他情况视为等于，返回 0.
	 */
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

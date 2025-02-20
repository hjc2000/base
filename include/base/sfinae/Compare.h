#pragma once
#include <base/string/define.h>
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

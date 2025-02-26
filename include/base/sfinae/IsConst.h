#pragma once
#include <base/define.h>

namespace base
{
	/**
	 * @brief 检查一个类型是否是 const
	 *
	 * @note 通过模板全特化实现。这里是没有特化的版本，Value 属性是 false，
	 * 再定义一个特化版本，匹配 Type const，特化版本的 Value 属性是 true。
	 * 这样就能通过匹配不同的特化版本来检查一个类型是否是 const。
	 *
	 * @tparam Type
	 */
	template <typename Type>
	struct is_const
	{
		static_function consteval bool Value()
		{
			return false;
		}
	};

	/**
	 * @brief 检查一个类型是否是 const。
	 *
	 * @note 这里是 Type const 的特化版本。使用时，当尖括号中的类型是 const 的时，
	 * 就会匹配到本特化版本，而不是上方的非特化版本。
	 *
	 * @tparam Type
	 */
	template <typename Type>
	struct is_const<Type const>
	{
		static_function consteval bool Value()
		{
			return true;
		}
	};

	/**
	 * @brief 封装 is_const 模板
	 *
	 * @tparam T
	 * @return consteval
	 */
	template <typename T>
	consteval bool IsConstType()
	{
		return is_const<T>::Value();
	}
} // namespace base

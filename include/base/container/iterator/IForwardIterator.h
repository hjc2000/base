#pragma once

namespace base
{
	/// @brief C++ 风格的正向迭代器接口。
	/// @tparam TypeSelf 本接口的派生类将 TypeSelf 设置为自己的类型。
	/// @tparam ItemType 被迭代元素的类型。
	template <typename TypeSelf, typename ItemType>
	class IForwardIterator
	{
	public:
		/// @brief 解引用。
		/// @return
		virtual ItemType &operator*() = 0;

		/// @brief 前缀递增。
		/// @return
		virtual TypeSelf &operator++() = 0;

		/// @brief 相等运算符。
		/// @param o
		/// @return
		virtual bool operator==(TypeSelf const &o) const = 0;

#pragma region 扩展

		/// @brief 后缀递增。
		/// @param
		/// @return
		virtual TypeSelf &operator++(int)
		{
			return operator++();
		}

		/// @brief 成员访问运算符。
		/// @return
		ItemType *operator->()
		{
			return &operator*();
		}

		/// @brief 不等运算符。
		/// @param o
		/// @return
		bool operator!=(TypeSelf const &o) const
		{
			return !(*this == o);
		}

#pragma endregion
	};
} // namespace base

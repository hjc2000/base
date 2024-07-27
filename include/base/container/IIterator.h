#pragma once

namespace base
{
	/// @brief 迭代器接口。
	/// @tparam TypeSelf 本接口的派生类将 TypeSelf 设置为自己的类型。
	/// @tparam ItemType 被迭代元素的类型。
	template <typename TypeSelf, typename ItemType>
	class IForwardIterator
	{
	public:
		/// @brief 解引用
		/// @return
		virtual ItemType &operator*() = 0;

		/// @brief 前缀递增
		/// @return
		virtual TypeSelf &operator++() = 0;

		virtual bool operator==(TypeSelf const &o) const = 0;

#pragma region 扩展
		/// @brief 后缀递增
		/// @param
		/// @return
		virtual TypeSelf &operator++(int)
		{
			return operator++();
		}

		ItemType *operator->()
		{
			return &operator*();
		}

		bool operator!=(TypeSelf const &o) const
		{
			return !(*this == o);
		}
#pragma endregion
	};
}

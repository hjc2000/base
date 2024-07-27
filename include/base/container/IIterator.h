#pragma once

namespace base
{
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
	};
}

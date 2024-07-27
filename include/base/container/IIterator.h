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

		ItemType *operator->()
		{
			return &operator*();
		}

		/// @brief 前缀递增
		/// @return
		virtual TypeSelf &operator++() = 0;

		/// @brief 后缀递增
		/// @param
		/// @return
		virtual TypeSelf &operator++(int)
		{
			return operator++();
		}

		virtual bool operator==(TypeSelf const &o) const = 0;

		bool operator!=(TypeSelf const &o) const
		{
			return !(*this == o);
		}
	};
}

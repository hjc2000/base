#pragma once
#include "base/container/iterator/IEnumerable.h"

namespace base
{
	template <typename ItemType>
	class ISet :
		public base::IEnumerable<ItemType const>
	{
	public:
		/* #region 接口 */

		///
		/// @brief 向集合中添加一个元素。
		///
		/// @param item
		///
		/// @return 如果集合中原本没有该元素，则添加成功，返回 true, 否则返回 false.
		///
		virtual bool Add(ItemType const &item) = 0;

		///
		/// @brief 移除指定的元素。
		///
		/// @param item
		///
		/// @return 集合中有该元素，移除成功则返回 true, 否则返回 false.
		///
		virtual bool Remove(ItemType const &item) = 0;

		///
		/// @brief 清空元素。
		///
		/// @return
		///
		virtual void Clear() = 0;

		///
		/// @brief 检查是否存在指定元素。
		///
		/// @param item
		///
		/// @return
		///
		virtual bool Contains(ItemType const &item) const = 0;

		///
		/// @brief 元素个数。
		///
		/// @return
		///
		virtual int64_t Count() const = 0;

		using base::IEnumerable<ItemType const>::GetEnumerator;

		///
		/// @brief 获取非 const 迭代器
		///
		/// @return
		///
		virtual std::shared_ptr<base::IEnumerator<ItemType const>> GetEnumerator() = 0;

		/* #endregion */

		/* #region Add */

		///
		/// @brief 将另一个集合的元素添加进来。
		///
		/// @param set
		///
		void Add(ISet<ItemType> const &set)
		{
			for (ItemType const &item : set)
			{
				Add(item);
			}
		}

		///
		/// @brief 将另一个可迭代容器的元素添加到本容器。
		///
		/// @param items
		///
		void Add(base::IEnumerable<ItemType> const &items)
		{
			for (ItemType const &item : items)
			{
				Add(item);
			}
		}

		///
		/// @brief 将另一个可迭代容器的元素添加到本容器。
		///
		/// @param items
		///
		void Add(base::IEnumerable<ItemType const> const &items)
		{
			for (ItemType const &item : items)
			{
				Add(item);
			}
		}

		/* #endregion */

		///
		/// @brief 从本集合中移除另一个集合 set 中含有的元素。
		///
		/// @param set
		///
		void Remove(ISet<ItemType> const &set)
		{
			for (ItemType const &item : set)
			{
				Remove(item);
			}
		}
	};

} // namespace base

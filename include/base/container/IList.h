#pragma once
#include "base/container/IQueue.h"
#include "base/container/iterator/IEnumerable.h"
#include "base/sfinae/Compare.h"
#include "base/sfinae/Equal.h"
#include <cstdint>
#include <functional>

namespace base
{
	///
	/// @brief 列表接口。
	///
	///
	template <typename ItemType>
	class IList :
		public virtual base::IEnumerable<ItemType>
	{
	private:
		/* #region 迭代器 */

		///
		/// @brief 用来迭代 IList 的私有迭代器。
		///
		///
		template <typename item_type>
		class Enumerator final :
			public base::IEnumerator<item_type>
		{
		private:
			IList<item_type> *_list;
			int32_t _index = 0;

		public:
			Enumerator(IList<item_type> *list)
			{
				_list = list;
			}

			///
			/// @brief 迭代器当前是否指向尾后元素。
			///
			/// @return
			///
			virtual bool IsEnd() const override
			{
				return _index == _list->Count();
			}

			///
			/// @brief 获取当前值的引用。
			///
			/// @return ItemType&
			///
			virtual item_type &CurrentValue() override
			{
				return (*_list)[_index];
			}

			///
			/// @brief 递增迭代器的位置。
			///
			///
			virtual void Add() override
			{
				++_index;
			}
		};

		/* #endregion */

	public:
		/* #region 接口 */

		///
		/// @brief 向列表末尾添加一个元素。
		///
		/// @param item
		///
		virtual void Add(ItemType const &item) = 0;

		///
		/// @brief 将元素插入列表指定位置。
		///
		/// @param index
		/// @param item
		///
		virtual void Insert(int32_t index, ItemType const &item) = 0;

		///
		/// @brief 从列表移除指定元素。
		///
		/// @note 如果列表中有重复元素，调用一次本方法只会移除一个。
		///
		/// @param item
		/// @return true
		/// @return false
		///
		virtual bool Remove(ItemType const &item) = 0;

		///
		/// @brief 移除指定索引位置的元素。
		///
		/// @param index
		///
		virtual void RemoveAt(int32_t index) = 0;

		///
		/// @brief 移除符合条件的数据。
		///
		/// @param should_remove 用来指示特定的元素是否应该从容器中移除。
		///
		virtual void RemoveIf(std::function<bool(ItemType const &item)> should_remove) = 0;

		///
		/// @brief 查找指定元素的索引。
		///
		/// @param item
		/// @return int32_t
		///
		virtual int32_t IndexOf(ItemType const &item) const = 0;

		///
		/// @brief 检查列表中是否含有该元素。
		///
		/// @param item
		/// @return true
		/// @return false
		///
		virtual bool Contains(ItemType const &item) const = 0;

		///
		/// @brief 清空列表。
		///
		///
		virtual void Clear() = 0;

		///
		/// @brief 列表中元素的数量。
		///
		/// @note 这里没有必要使用 size_t 来支持超过 2147483647 个元素，因为 qt 的表格数据模型
		/// 本身索引行列和计算元素数量都是使用 int, 不支持很庞大的数量级。如果真的很多的话需要分页
		/// 处理。
		///
		/// @note 使用 int32_t 的好处：
		/// 	@li 现在嵌入式系统普遍是 32 位的，直接使用 int32_t 可以在各个平台一致，不用考虑
		/// 		size_t 在不同平台上的差异。
		///
		/// 	@li 嵌入式平台使用 int32_t 性能更高。
		///
		/// 	@li 使用 int32_t, 是有符号整型，比较大小比较方便。如果使用 size_t,
		/// 		要额外处理和有符号整型的大小比较。
		///
		/// @return int32_t
		///
		virtual int32_t Count() const = 0;

		///
		/// @brief 获取指定索引位置的元素。
		///
		/// @param index
		/// @return ItemType&
		///
		virtual ItemType &operator[](int32_t index) = 0;

		///
		/// @brief 获取指定索引位置的元素。
		///
		/// @param index
		/// @return ItemType const&
		///
		virtual ItemType const &operator[](int32_t index) const = 0;

		/* #endregion */

		/* #region Add */

		///
		/// @brief 将另一个列表的元素添加到本列表中。
		///
		/// @param list
		///
		void Add(IList<ItemType> const &list)
		{
			for (ItemType const &item : list)
			{
				Add(item);
			}
		}

		///
		/// @brief 将队列的元素添加到本列表中，添加的同时会退队。
		///
		/// @param queue
		///
		void Add(base::IQueue<ItemType> &queue)
		{
			ItemType item{};
			while (queue.TryDequeue(item))
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

		///
		/// @brief 将初始化列表的元素添加到本列表中。
		///
		/// @param list
		///
		void Add(std::initializer_list<ItemType> const &list)
		{
			for (ItemType const &item : list)
			{
				Add(item);
			}
		}

		///
		/// @brief 将向量中的元素添加到本列表中。
		///
		/// @param list
		///
		void Add(std::vector<ItemType> const &list)
		{
			for (ItemType const &item : list)
			{
				Add(item);
			}
		}

		///
		/// @brief 将数组的元素添加到本列表。
		///
		/// @param list
		/// @return
		///
		template <int32_t Count>
		void Add(std::array<ItemType, Count> const &list)
		{
			for (ItemType const &item : list)
			{
				Add(item);
			}
		}

		/* #endregion */

		/* #region GetEnumerator */

		using base::IEnumerable<ItemType>::GetEnumerator;

		///
		/// @brief 获取迭代器
		///
		/// @return std::shared_ptr<IEnumerator<ItemType>>
		///
		virtual std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() override
		{
			return std::shared_ptr<IEnumerator<ItemType>>{new Enumerator<ItemType>{this}};
		}

		/* #endregion */

		/* #region 比较运算符 */

		bool operator==(IList<ItemType> const &o) const
			requires(base::has_equal_operator<ItemType> &&
					 base::has_less_than_operator<ItemType> &&
					 base::has_greater_than_operator<ItemType>)
		{
			if (this == &o)
			{
				return true;
			}

			if (Count() != o.Count())
			{
				return false;
			}

			// 执行到这里说明 Count 相等。
			for (int32_t i = 0; i < Count(); i++)
			{
				if ((*this)[i] != o[i])
				{
					return false;
				}
			}

			return true;
		}

		bool operator<(IList<ItemType> const &o) const
			requires(base::has_equal_operator<ItemType> &&
					 base::has_less_than_operator<ItemType> &&
					 base::has_greater_than_operator<ItemType>)
		{
			if (this == &o)
			{
				return false;
			}

			int32_t count = std::min(Count(), o.Count());
			for (int32_t i = 0; i < count; i++)
			{
				if ((*this)[i] < o[i])
				{
					return true;
				}

				if ((*this)[i] > o[i])
				{
					return false;
				}

				// 相等就继续下一轮循环
			}

			// 经过循环后还没返回，说明比较结果都是相等。接下来比较长度。
			return Count() < o.Count();
		}

		bool operator>(IList<ItemType> const &o) const
			requires(base::has_equal_operator<ItemType> &&
					 base::has_less_than_operator<ItemType> &&
					 base::has_greater_than_operator<ItemType>)
		{
			if (this == &o)
			{
				return false;
			}

			int32_t count = std::min(Count(), o.Count());
			for (int32_t i = 0; i < count; i++)
			{
				if ((*this)[i] > o[i])
				{
					return true;
				}

				if ((*this)[i] < o[i])
				{
					return false;
				}

				// 相等就继续下一轮循环
			}

			// 经过循环后还没返回，说明比较结果都是相等。接下来比较长度。
			return Count() > o.Count();
		}

		bool operator<=(IList<ItemType> const &o) const
			requires(base::has_equal_operator<ItemType> &&
					 base::has_less_than_operator<ItemType> &&
					 base::has_greater_than_operator<ItemType>)
		{
			if (this == &o)
			{
				return false;
			}

			int32_t count = std::min(Count(), o.Count());
			for (int32_t i = 0; i < count; i++)
			{
				if ((*this)[i] < o[i])
				{
					return true;
				}

				if ((*this)[i] > o[i])
				{
					return false;
				}

				// 相等就继续下一轮循环
			}

			// 经过循环后还没返回，说明比较结果都是相等。接下来比较长度。
			return Count() <= o.Count();
		}

		bool operator>=(IList<ItemType> const &o) const
			requires(base::has_equal_operator<ItemType> &&
					 base::has_less_than_operator<ItemType> &&
					 base::has_greater_than_operator<ItemType>)
		{
			if (this == &o)
			{
				return false;
			}

			int32_t count = std::min(Count(), o.Count());
			for (int32_t i = 0; i < count; i++)
			{
				if ((*this)[i] > o[i])
				{
					return true;
				}

				if ((*this)[i] < o[i])
				{
					return false;
				}

				// 相等就继续下一轮循环
			}

			// 经过循环后还没返回，说明比较结果都是相等。接下来比较长度。
			return Count() >= o.Count();
		}

		/* #endregion */
	};
} // namespace base

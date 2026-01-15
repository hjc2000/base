#pragma once
#include "base/container/iterator/IEnumerable.h"
#include "base/container/iterator/IRandomAccessEnumerable.h"
#include "base/container/iterator/IRandomAccessEnumerator.h"
#include "base/math/math.h"
#include "base/sfinae/Compare.h"
#include <array>
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <vector>

namespace base
{
	///
	/// @brief 列表接口。
	///
	///
	template <typename ItemType>
	class IList :
		public virtual base::IRandomAccessEnumerable<ItemType>
	{
	private:
		/* #region 迭代器 */

		class RandomAccessEnumerator final :
			public base::IRandomAccessEnumerator<ItemType>
		{
		private:
			base::IList<ItemType> *_list;
			int64_t _index = 0;
			base::IEnumerator<ItemType>::Context_t _context{};

		public:
			RandomAccessEnumerator(base::IList<ItemType> *list)
			{
				_list = list;
			}

			///
			/// @brief 克隆一个迭代器对象副本。
			///
			/// @return
			///
			virtual std::shared_ptr<base::IRandomAccessEnumerator<ItemType>> Clone() const override
			{
				std::shared_ptr<base::IRandomAccessEnumerator<ItemType>> ret{new RandomAccessEnumerator{*this}};
				return ret;
			}

			///
			/// @brief 容器中总共有多少个元素。
			///
			/// @return
			///
			virtual int64_t Count() const override
			{
				return _list->Count();
			}

			///
			/// @brief 当前迭代到的位置。
			///
			/// @return
			///
			virtual int64_t Position() const override
			{
				return _index;
			}

			///
			/// @brief 将迭代器位置增加 value.
			///
			/// @param value 增加的值。可以是正数和负数。
			///
			virtual void Add(int64_t value) override
			{
				_index += value;
			}

			///
			/// @brief 获取当前值的引用。
			///
			/// @note 迭代器构造后，如果被迭代的集合不为空，要立即让 CurrentValue 指向第一个有效元素。
			///
			/// @return
			///
			virtual ItemType &CurrentValue() override
			{
				return _list->Get(_index);
			}

			///
			/// @brief 派生类需要提供一个该对象。
			///
			/// @return
			///
			virtual base::IEnumerator<ItemType>::Context_t &Context() override
			{
				return _context;
			}
		};

		/* #endregion */

	public:
		virtual ~IList() = default;

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
		virtual void Insert(int64_t index, ItemType const &item) = 0;

		///
		/// @brief 移除指定索引位置的元素。
		///
		/// @param index
		///
		virtual void RemoveAt(int64_t index) = 0;

		///
		/// @brief 清空列表。
		///
		///
		virtual void Clear() = 0;

		///
		/// @brief 列表中元素的数量。
		///
		/// @return
		///
		virtual int64_t Count() const = 0;

		///
		/// @brief 获取指定索引位置的元素。
		///
		/// @param index
		///
		/// @return
		///
		virtual ItemType &Get(int64_t index) = 0;

		///
		/// @brief 获取指定索引位置的元素。
		///
		/// @param index
		///
		/// @return
		///
		virtual ItemType const &Get(int64_t index) const = 0;

		///
		/// @brief 设置指定位置的元素。
		///
		/// @param index
		/// @param value
		///
		virtual void Set(int64_t index, ItemType const &value) = 0;

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
		///
		/// @return
		///
		template <int64_t Count>
		void Add(std::array<ItemType, Count> const &list)
		{
			for (ItemType const &item : list)
			{
				Add(item);
			}
		}

		/* #endregion */

		/* #region 二分法查找 */

		///
		/// @brief 升序排列时适用的二分法查找。
		///
		/// @return 找到了返回元素的索引，找不到返回 -1.
		///
		int64_t AscendingOrderBinarySearch(ItemType const &item) const
			requires(base::has_all_compare_operators<ItemType, ItemType>)
		{
			int64_t left = 0;
			int64_t right = Count() - 1;

			while (left <= right)
			{
				int64_t middle = left + (right - left) / 2;
				ItemType const &middle_item = Get(middle);
				if (middle_item == item)
				{
					return middle;
				}

				if (item < middle_item)
				{
					// item 在 middle_item 左边
					right = middle - 1;
					continue;
				}

				// item 在 middle_item 右边
				left = middle + 1;
			}

			return -1;
		}

		///
		/// @brief 升序排列时适用的二分法查找。
		///
		/// @param compare 比较器。返回负数表示左边小于右边，返回 0 表示等于，返回正数表示左边大于右边。
		///
		/// @return 找到了返回元素的索引，找不到返回 -1.
		///
		int64_t AscendingOrderBinarySearch(ItemType const &item,
										   std::function<int64_t(ItemType const &left, ItemType const &right)> compare) const
		{
			int64_t left = 0;
			int64_t right = Count() - 1;

			while (left <= right)
			{
				int64_t middle = left + (right - left) / 2;
				ItemType const &middle_item = Get(middle);
				int64_t compare_result = compare(item, middle_item);

				if (compare_result == 0)
				{
					return middle;
				}

				if (compare_result < 0)
				{
					// item 在 middle_item 左边
					right = middle - 1;
					continue;
				}

				// item 在 middle_item 右边
				left = middle + 1;
			}

			return -1;
		}

		///
		/// @brief 升序排列时适用的二分法查找。
		///
		/// @return 找到了返回元素的索引，找不到返回 -1.
		///
		int64_t DescendingOrderBinarySearch(ItemType const &item) const
			requires(base::has_all_compare_operators<ItemType, ItemType>)
		{
			int64_t left = 0;
			int64_t right = Count() - 1;

			while (left <= right)
			{
				int64_t middle = left + (right - left) / 2;
				ItemType const &middle_item = Get(middle);
				if (middle_item == item)
				{
					return middle;
				}

				if (item < middle_item)
				{
					// item 在 middle_item 右边
					left = middle + 1;
					continue;
				}

				// item 在 middle_item 左边
				right = middle - 1;
			}

			return -1;
		}

		///
		/// @brief 升序排列时适用的二分法查找。
		///
		/// @param compare 比较器。返回负数表示左边小于右边，返回 0 表示等于，返回正数表示左边大于右边。
		///
		/// @return 找到了返回元素的索引，找不到返回 -1.
		///
		int64_t DescendingOrderBinarySearch(ItemType const &item,
											std::function<int64_t(ItemType const &left, ItemType const &right)> compare) const
		{
			int64_t left = 0;
			int64_t right = Count() - 1;

			while (left <= right)
			{
				int64_t middle = left + (right - left) / 2;
				ItemType const &middle_item = Get(middle);
				int64_t compare_result = compare(item, middle_item);

				if (compare_result == 0)
				{
					return middle;
				}

				if (compare_result < 0)
				{
					// item 在 middle_item 右边
					left = middle + 1;
					continue;
				}

				// item 在 middle_item 左边
				right = middle - 1;
			}

			return -1;
		}

		/* #endregion */

		/* #region 二分法近似查找 */

		///
		/// @brief 升序排列时适用的二分法查找。查找最接近 item 的元素的索引。
		///
		/// @param compare 比较器。返回左边的对象和右边的对象的距离，即 left - right.
		///
		/// @return 返回最接近 item 的元素的索引。列表为空时会直接返回 -1.
		///
		int64_t AscendingOrderBinarySearchAround(ItemType const &item,
												 std::function<int64_t(ItemType const &left, ItemType const &right)> compare) const
		{
			if (Count() <= 0)
			{
				return -1;
			}

			int64_t left = 0;
			int64_t right = Count() - 1;

			int64_t closest_distance = compare(item, Get(left));
			closest_distance = base::abs(closest_distance);
			int64_t closest_item_index = left;

			while (left <= right)
			{
				int64_t middle = left + (right - left) / 2;
				ItemType const &middle_item = Get(middle);
				int64_t compare_result = compare(item, middle_item);

				if (compare_result == 0)
				{
					return middle;
				}

				int64_t distance = base::abs(compare_result);
				if (distance < closest_distance)
				{
					closest_distance = distance;
					closest_item_index = middle;
				}

				if (compare_result < 0)
				{
					// item 在 middle_item 左边
					right = middle - 1;
					continue;
				}

				// item 在 middle_item 右边
				left = middle + 1;
			}

			return closest_item_index;
		}

		///
		/// @brief 降序排列时适用的二分法查找。查找最接近 item 的元素的索引。
		///
		/// @param compare 比较器。返回左边的对象和右边的对象的距离，即 left - right.
		///
		/// @return 返回最接近 item 的元素的索引。列表为空时会直接返回 -1.
		///
		int64_t DescendingOrderBinarySearchAround(ItemType const &item,
												  std::function<int64_t(ItemType const &left, ItemType const &right)> compare) const
		{
			if (Count() <= 0)
			{
				return -1;
			}

			int64_t left = 0;
			int64_t right = Count() - 1;

			int64_t closest_distance = compare(item, Get(left));
			closest_distance = base::abs(closest_distance);
			int64_t closest_item_index = left;

			while (left <= right)
			{
				int64_t middle = left + (right - left) / 2;
				ItemType const &middle_item = Get(middle);
				int64_t compare_result = compare(item, middle_item);

				if (compare_result == 0)
				{
					return middle;
				}

				int64_t distance = base::abs(compare_result);
				if (distance < closest_distance)
				{
					closest_distance = distance;
					closest_item_index = middle;
				}

				if (compare_result < 0)
				{
					// item 在 middle_item 右边
					left = middle + 1;
					continue;
				}

				// item 在 middle_item 左边
				right = middle - 1;
			}

			return closest_item_index;
		}

		/* #endregion */

		/* #region GetRandomAccessEnumerator */

		using base::IRandomAccessEnumerable<ItemType>::GetRandomAccessEnumerator;

		///
		/// @brief 获取非 const 迭代器
		///
		/// @return
		///
		virtual std::shared_ptr<base::IRandomAccessEnumerator<ItemType>> GetRandomAccessEnumerator() override
		{
			return std::shared_ptr<base::IRandomAccessEnumerator<ItemType>>{new RandomAccessEnumerator{this}};
		}

		/* #endregion */

		/* #region 比较运算符 */

		bool operator==(IList<ItemType> const &o) const
			requires(base::has_all_compare_operators<ItemType, ItemType>)
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
			for (int64_t i = 0; i < Count(); i++)
			{
				if (Get(i) != o.Get(i))
				{
					return false;
				}
			}

			return true;
		}

		bool operator<(IList<ItemType> const &o) const
			requires(base::has_all_compare_operators<ItemType, ItemType>)
		{
			if (this == &o)
			{
				return false;
			}

			int64_t count = std::min(Count(), o.Count());
			for (int64_t i = 0; i < count; i++)
			{
				if (Get(i) < o.Get(i))
				{
					return true;
				}

				if (Get(i) > o.Get(i))
				{
					return false;
				}

				// 相等就继续下一轮循环
			}

			// 经过循环后还没返回，说明比较结果都是相等。接下来比较长度。
			return Count() < o.Count();
		}

		bool operator>(IList<ItemType> const &o) const
			requires(base::has_all_compare_operators<ItemType, ItemType>)
		{
			if (this == &o)
			{
				return false;
			}

			int64_t count = std::min(Count(), o.Count());
			for (int64_t i = 0; i < count; i++)
			{
				if (Get(i) > o.Get(i))
				{
					return true;
				}

				if (Get(i) < o.Get(i))
				{
					return false;
				}

				// 相等就继续下一轮循环
			}

			// 经过循环后还没返回，说明比较结果都是相等。接下来比较长度。
			return Count() > o.Count();
		}

		bool operator<=(IList<ItemType> const &o) const
			requires(base::has_all_compare_operators<ItemType, ItemType>)
		{
			if (this == &o)
			{
				return false;
			}

			int64_t count = std::min(Count(), o.Count());
			for (int64_t i = 0; i < count; i++)
			{
				if (Get(i) < o.Get(i))
				{
					return true;
				}

				if (Get(i) > o.Get(i))
				{
					return false;
				}

				// 相等就继续下一轮循环
			}

			// 经过循环后还没返回，说明比较结果都是相等。接下来比较长度。
			return Count() <= o.Count();
		}

		bool operator>=(IList<ItemType> const &o) const
			requires(base::has_all_compare_operators<ItemType, ItemType>)
		{
			if (this == &o)
			{
				return false;
			}

			int64_t count = std::min(Count(), o.Count());
			for (int64_t i = 0; i < count; i++)
			{
				if (Get(i) > o.Get(i))
				{
					return true;
				}

				if (Get(i) < o.Get(i))
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

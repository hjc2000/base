#pragma once
#include "base/container/iterator/IEnumerable.h"
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
	class IList
	{
	private:
	public:
		/* #region 迭代器 */

		template <typename item_type>
		class Iterator
		{
		private:
			IList *_array = nullptr;
			int64_t _index = 0;

		public:
			using iterator_category = std::random_access_iterator_tag;
			using value_type = item_type;
			using difference_type = int64_t;
			using pointer = item_type *;
			using reference = item_type &;

			Iterator() = default;

			Iterator(IList *array, int64_t index)
			{
				_array = array;
				_index = index;
			}

			item_type &operator*()
			{
				if (_array == nullptr)
				{
					throw std::invalid_argument{CODE_POS_STR + "迭代器处于无效状态。"};
				}

				return (*_array)[_index];
			}

			item_type *operator->()
			{
				return &operator*();
			}

			///
			/// @brief 前缀递增
			///
			/// @return
			///
			Iterator &operator++()
			{
				_index++;
				return *this;
			}

			///
			/// @brief 后缀递增。
			///
			Iterator operator++(int)
			{
				Iterator copy{*this};
				_index++;
				return copy;
			}

			///
			/// @brief 前缀递减。
			///
			/// @return
			///
			Iterator &operator--()
			{
				_index--;
				return *this;
			}

			///
			/// @brief 后缀递减。
			///
			/// @return
			///
			Iterator operator--(int)
			{
				Iterator copy{*this};
				_index--;
				return copy;
			}

			Iterator &operator+=(int64_t value)
			{
				_index += value;
				return *this;
			}

			Iterator operator+(int64_t value) const
			{
				Iterator copy{*this};
				copy += value;
				return copy;
			}

			int64_t operator-(Iterator const &other) const
			{
				return _index - other._index;
			}

			bool operator==(Iterator const &other) const
			{
				return _index == other._index;
			}

			bool operator!=(Iterator const &other) const
			{
				return !(*this == other);
			}
		};

		/* #endregion */

	private:
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

		ItemType &operator[](int64_t index)
		{
			return Get(index);
		}

		ItemType const &operator[](int64_t index) const
		{
			return Get(index);
		}

		Iterator<ItemType> begin()
		{
			return Iterator<ItemType>{this, 0};
		}

		Iterator<ItemType> end()
		{
			return Iterator<ItemType>{this, Count()};
		}

		Iterator<ItemType const> begin() const
		{
			return Iterator<ItemType const>{const_cast<IList *>(this), 0};
		}

		Iterator<ItemType const> end() const
		{
			return Iterator<ItemType const>{const_cast<IList *>(this), Count()};
		}
	};

} // namespace base

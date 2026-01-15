#pragma once
#include "base/container/IList.h"
#include "base/sfinae/Compare.h"
#include "base/string/define.h"
#include <algorithm>
#include <cstdint>
#include <deque>
#include <stdexcept>

namespace base
{
	///
	/// @brief 封装 std::deque 的列表。
	///
	template <typename ItemType>
	class ChunkedList final :
		public base::IList<ItemType>
	{
	private:
		std::deque<ItemType> _deque;

	public:
		/* #region 构造函数 */

		ChunkedList() = default;

		ChunkedList(std::deque<ItemType> const &o)
		{
			_deque = o;
		}

		ChunkedList(std::initializer_list<ItemType> const &list)
		{
			_deque = list;
		}

		/* #endregion */

		explicit operator std::deque<ItemType>() const
		{
			return _deque;
		}

		///
		/// @brief 保留一定的空间。
		///
		/// @note 如果提前知道会有多少个数据，先保留空间后再插入数据可以避免不断动态扩容从而
		/// 不断发生拷贝。
		///
		/// @param size
		///
		void Reserve(int64_t size)
		{
			// std::deque 是需要扩容时额外申请一块内存链接到块链表中，不需要像其他容器那样
			// 为了高效添加数据预先保留一块内存。
			//
			// std::deque 本身也没有提供预先保留空间的方法。
		}

		/* #region 添加元素 */

		using IList<ItemType>::Add;

		///
		/// @brief 向列表末尾添加一个元素。
		///
		/// @param item
		///
		virtual void Add(ItemType const &item) override
		{
			_deque.push_back(item);
		}

		using IList<ItemType>::Insert;

		///
		/// @brief 将元素插入列表指定位置。
		///
		/// @param index
		/// @param item
		///
		virtual void Insert(int64_t index, ItemType const &item) override
		{
			if (index < 0 || index > static_cast<int64_t>(_deque.size()))
			{
				throw std::out_of_range{"索引超出范围"};
			}

			_deque.insert(_deque.begin() + index, item);
		}

		void Insert(int64_t index, base::IList<ItemType> const &list)
		{
			_deque.insert(_deque.begin() + index,
						  list.begin(),
						  list.end());
		}

		/* #endregion */

		/* #region 移除元素 */

		///
		/// @brief 从列表移除指定元素。
		///
		/// @note 如果列表中有重复元素，调用一次本方法只会移除一个。
		///
		/// @param item
		///
		/// @return
		///
		bool Remove(ItemType const &item)
			requires(base::has_equal_operator<ItemType, ItemType>)
		{
			auto it = std::find_if(_deque.begin(),
								   _deque.end(),
								   [&](ItemType const &p)
								   {
									   return p == item;
								   });

			if (it != _deque.end())
			{
				_deque.erase(it);
				return true; // 返回 true 表示成功找到并删除了元素
			}

			// 如果没有找到元素，返回 false
			return false;
		}

		///
		/// @brief 移除指定索引位置的元素。
		///
		/// @param index
		///
		virtual void RemoveAt(int64_t const index) override
		{
			if (index < 0 || index >= static_cast<int64_t>(_deque.size()))
			{
				throw std::out_of_range{"索引超出范围"};
			}

			_deque.erase(_deque.begin() + index);
		}

		///
		/// @brief 移除符合条件的数据。
		///
		/// @param should_remove 用来指示特定的元素是否应该从容器中移除。
		///
		void RemoveIf(std::function<bool(ItemType const &item)> should_remove)
		{
			// 为了避免每移除一个元素就将后面位置的元素向前移动，造成开销过大。可以准备一个临时的容器，
			// 不需要移除的元素就添加到临时容器，需要移除的就跳过。最后，用临时容器替换掉原来的容器。
			//
			// 进一步改进可以把临时容器取消，直接原地操作。准备一个读指针，用来遍历容器，准备一个写指针，
			// 用来写入不需要移除的元素。在写指针的位置写入就相当于写入临时容器。
			//
			// 遍历原容器，在遍历过程中递增读指针。当前元素不需要移除，就写入写指针的位置，然后递增写指针。
			// 当前元素需要移除，就跳过，即只递增读指针，不递增写指针。
			//
			// 最后，写指针的前方就是需要保留的元素，写指针后方的元素是垃圾数据，这其中包括了需要移除的
			// 元素和不需要移除的元素，它们已经被读指针经过了。其中不需要移除的元素已经被复制到前面了。
			//
			// remove_if 最后返回的就是写指针，从写指针到尾指针的这段都是需要去掉的垃圾数据。
			//
			auto remove_begin = std::remove_if(_deque.begin(),
											   _deque.end(),
											   [&](ItemType const &item)
											   {
												   return should_remove(item);
											   });

			_deque.erase(remove_begin, _deque.end());
		}

		///
		/// @brief 清空列表。
		///
		///
		virtual void Clear() override
		{
			_deque.clear();
		}

		/* #endregion */

		/* #region 查找元素 */

		///
		/// @brief 查找指定元素的索引。
		///
		/// @param item
		///
		/// @return
		///
		int64_t IndexOf(ItemType const &item) const
			requires(base::has_equal_operator<ItemType, ItemType>)
		{
			auto it = std::find_if(_deque.begin(),
								   _deque.end(),
								   [&](ItemType const &p)
								   {
									   return p == item;
								   });

			if (it != _deque.end())
			{
				return static_cast<int64_t>(std::distance(_deque.begin(), it)); // 返回元素的索引
			}

			// 如果没有找到元素，返回 -1
			return -1;
		}

		///
		/// @brief 检查列表中是否含有该元素。
		///
		/// @param item
		///
		/// @return
		///
		bool Contains(ItemType const &item) const
			requires(base::has_equal_operator<ItemType, ItemType>)
		{
			auto it = std::find_if(_deque.begin(),
								   _deque.end(),
								   [&](ItemType const &p)
								   {
									   return p == item;
								   });

			return it != _deque.end();
		}

		/* #endregion */

		///
		/// @brief 列表中元素的数量。
		///
		/// @return
		///
		virtual int64_t Count() const override
		{
			return static_cast<int64_t>(_deque.size());
		}

		/* #region Sort */

		///
		/// @brief 排序。
		///
		/// @param ascending 是否按升序排序，即从小到大排序。传入 true 则按升序排序，传入 false 则按降序排序。
		///
		/// @warning 需要 ItemType 实现了比较运算符，否则会引发异常。
		///
		void Sort(bool ascending = true)
			requires(has_all_compare_operators<ItemType, ItemType>)
		{
			try
			{
				std::stable_sort(_deque.begin(),
								 _deque.end(),
								 [ascending](ItemType const &left, ItemType const &right) -> bool
								 {
									 if (ascending)
									 {
										 // std::stable_sort 函数的机制是如果谓语返回 true, 则将 left 排到 right
										 // 的前面，否则就不调整 left 和 right 的顺序。
										 //
										 // 如果返回的是 base::LessThan, 则小于的时候谓语返回 true, left 排到
										 // right 前面，那这就是升序排列，即从小到大排列。
										 return left < right;
									 }
									 else
									 {
										 return left > right;
									 }
								 });
			}
			catch (std::exception const &e)
			{
				throw std::runtime_error{CODE_POS_STR + e.what()};
			}
		}

		///
		/// @brief 排序。
		///
		/// @param compare 谓语。如果希望 left 排到 right 前面，则返回 true. 如果返回 false,
		/// 则 left 和 right 会保持当前相对顺序，不会调整。
		///
		/// @note 可以实现升序、降序排列。
		/// 	@li 如果 compare 在 left < right 时返回 true, 则实现的是升序排列。
		/// 	@li 如果 compare 在 left > right 时返回 true, 则实现的是降序排列。
		///
		template <typename parameter_type>
		void Sort(parameter_type const &compare)
			requires(std::is_convertible_v<parameter_type, std::function<bool(ItemType const &left, ItemType const &right)>>)
		{
			try
			{
				std::stable_sort(_deque.begin(),
								 _deque.end(),
								 [&](ItemType const &left, ItemType const &right) -> bool
								 {
									 return compare(left, right);
								 });
			}
			catch (std::exception const &e)
			{
				throw std::runtime_error{CODE_POS_STR + e.what()};
			}
		}

		/* #endregion */

		/* #region 索引器 */

		///
		/// @brief 获取指定索引位置的元素。
		///
		/// @note 底层是多个内存块，扩容时会再申请一个内存块。这些内存块有一个索引表，当随机访问时，
		/// 传入 index, 计算
		/// 	size_t block_index = index / block_size;
		/// 	size_t element_index_within_block = index % block_size;
		/// block_index 用于在索引表中取出内存块的指针，element_index_within_block 用于在取出
		/// 内存块后在这个内存块内索引元素。
		///
		/// 所以随机访问的时间复杂度是 O(1).
		///
		/// @param index
		///
		/// @return
		///
		ItemType &operator[](int64_t const index)
		{
			return _deque[index];
		}

		///
		/// @brief 获取指定索引位置的元素。
		///
		/// @note 底层是多个内存块，扩容时会再申请一个内存块。这些内存块有一个索引表，当随机访问时，
		/// 传入 index, 计算
		/// 	size_t block_index = index / block_size;
		/// 	size_t element_index_within_block = index % block_size;
		/// block_index 用于在索引表中取出内存块的指针，element_index_within_block 用于在取出
		/// 内存块后在这个内存块内索引元素。
		///
		/// 所以随机访问的时间复杂度是 O(1).
		///
		/// @param index
		///
		/// @return
		///
		ItemType const &operator[](int64_t const index) const
		{
			return _deque[index];
		}

		///
		/// @brief 获取指定索引位置的元素。
		///
		/// @note 底层是多个内存块，扩容时会再申请一个内存块。这些内存块有一个索引表，当随机访问时，
		/// 传入 index, 计算
		/// 	size_t block_index = index / block_size;
		/// 	size_t element_index_within_block = index % block_size;
		/// block_index 用于在索引表中取出内存块的指针，element_index_within_block 用于在取出
		/// 内存块后在这个内存块内索引元素。
		///
		/// 所以随机访问的时间复杂度是 O(1).
		///
		/// @param index
		///
		/// @return
		///
		virtual ItemType &Get(int64_t index) override
		{
			return _deque[index];
		}

		///
		/// @brief 获取指定索引位置的元素。
		///
		/// @note 底层是多个内存块，扩容时会再申请一个内存块。这些内存块有一个索引表，当随机访问时，
		/// 传入 index, 计算
		/// 	size_t block_index = index / block_size;
		/// 	size_t element_index_within_block = index % block_size;
		/// block_index 用于在索引表中取出内存块的指针，element_index_within_block 用于在取出
		/// 内存块后在这个内存块内索引元素。
		///
		/// 所以随机访问的时间复杂度是 O(1).
		///
		/// @param index
		///
		/// @return
		///
		virtual ItemType const &Get(int64_t index) const override
		{
			return _deque[index];
		}

		///
		/// @brief 设置指定位置的元素。
		///
		/// @param index
		/// @param value
		///
		virtual void Set(int64_t index, ItemType const &value) override
		{
			_deque[index] = value;
		}

		/* #endregion */

		/* #region 比较运算符 */

		using base::IList<ItemType>::operator==;
		using base::IList<ItemType>::operator<;
		using base::IList<ItemType>::operator>;
		using base::IList<ItemType>::operator<=;
		using base::IList<ItemType>::operator>=;

		///
		/// @brief 转发到 std::vector 的相等判断逻辑。
		///
		/// @param another
		///
		/// @return
		///
		bool operator==(ChunkedList<ItemType> const &another) const
		{
			return _deque == another._deque;
		}

		/* #endregion */
	};

} // namespace base

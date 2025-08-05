#pragma once
#include "base/container/IList.h"
#include "base/container/IRawArray.h"
#include "base/container/iterator/IEnumerable.h"
#include "base/sfinae/Equal.h"
#include "base/string/define.h"
#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace base
{
	///
	/// @brief 基于 std::vector 的列表。
	///
	///
	template <typename ItemType>
	class List final :
		public base::IList<ItemType>,
		public base::IRawArray<ItemType>
	{
	private:
		std::vector<ItemType> _vector;

	public:
		/* #region 构造函数 */

		///
		/// @brief 构造一个空列表。
		///
		///
		List() = default;

		///
		/// @brief 从向量中构造。将向量的元素拷贝过来。
		///
		/// @param o
		///
		List(std::vector<ItemType> const &o)
		{
			_vector = o;
		}

		List(std::initializer_list<ItemType> const &list)
		{
			_vector = list;
		}

		/* #endregion */

		///
		/// @brief 将本列表内的元素拷贝到向量中。
		///
		/// @return
		///
		explicit operator std::vector<ItemType>() const
		{
			// 直接返回，利用 vector 的拷贝构造函数。
			return _vector;
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
			if (size < 0)
			{
				throw std::invalid_argument{CODE_POS_STR + "size 不能 < 0."};
			}

			_vector.reserve(size);
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
			_vector.push_back(item);
		}

		using IList<ItemType>::Insert;

		///
		/// @brief 将元素插入列表指定位置。
		///
		/// @param index
		/// @param item
		///
		virtual void Insert(int64_t const index, ItemType const &item) override
		{
			if (index < 0 || index > static_cast<int64_t>(_vector.size()))
			{
				throw std::out_of_range{CODE_POS_STR + "索引超出范围"};
			}

			_vector.insert(_vector.begin() + index, item);
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
		{
			auto it = std::find_if(_vector.begin(),
								   _vector.end(),
								   [&](ItemType const &p)
								   {
									   return base::Equal(p, item);
								   });

			if (it != _vector.end())
			{
				_vector.erase(it);
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
			if (index < 0 || index >= static_cast<int64_t>(_vector.size()))
			{
				throw std::out_of_range{"索引超出范围"};
			}

			_vector.erase(_vector.begin() + index);
		}

		///
		/// @brief 移除符合条件的数据。
		///
		/// @param should_remove 用来指示特定的元素是否应该从容器中移除。
		///
		virtual void RemoveIf(std::function<bool(ItemType const &item)> should_remove) override
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
			auto remove_begin = std::remove_if(_vector.begin(),
											   _vector.end(),
											   [&](ItemType const &item)
											   {
												   return should_remove(item);
											   });

			_vector.erase(remove_begin, _vector.end());
		}

		///
		/// @brief 清空列表。
		///
		///
		virtual void Clear() override
		{
			_vector.clear();
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
		virtual int64_t IndexOf(ItemType const &item) const override
		{
			auto it = std::find_if(_vector.begin(),
								   _vector.end(),
								   [&](ItemType const &p)
								   {
									   return base::Equal(p, item);
								   });

			if (it != _vector.end())
			{
				return static_cast<int64_t>(std::distance(_vector.begin(), it)); // 返回元素的索引
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
		virtual bool Contains(ItemType const &item) const override
		{
			auto it = std::find_if(_vector.begin(),
								   _vector.end(),
								   [&](ItemType const &p)
								   {
									   return base::Equal(p, item);
								   });

			return it != _vector.end();
		}

		/* #endregion */

		///
		/// @brief 列表中元素的数量。
		///
		/// @return
		///
		virtual int64_t Count() const override
		{
			return static_cast<int64_t>(_vector.size());
		}

		/* #region 索引器 */

		///
		/// @brief 获取指定索引位置的元素。
		///
		/// @param index
		///
		/// @return
		///
		ItemType &operator[](int64_t const index)
		{
			return IRawArray<ItemType>::operator[](index);
		}

		///
		/// @brief 获取指定索引位置的元素。
		///
		/// @param index
		///
		/// @return
		///
		ItemType const &operator[](int64_t const index) const
		{
			return IRawArray<ItemType>::operator[](index);
		}

		///
		/// @brief 获取指定索引位置的元素。
		///
		/// @param index
		///
		/// @return
		///
		virtual ItemType &Get(int64_t index) override
		{
			return IRawArray<ItemType>::operator[](index);
		}

		///
		/// @brief 获取指定索引位置的元素。
		///
		/// @param index
		///
		/// @return
		///
		virtual ItemType const &Get(int64_t index) const override
		{
			return IRawArray<ItemType>::operator[](index);
		}

		///
		/// @brief 设置指定位置的元素。
		///
		/// @param index
		/// @param value
		///
		virtual void Set(int64_t index, ItemType const &value) override
		{
			IRawArray<ItemType>::operator[](index) = value;
		}

		/* #endregion */

		/* #region Buffer */

		///
		/// @brief 获取底层的缓冲区。
		///
		///
		/// @return
		///
		virtual ItemType *Buffer() override
		{
			return _vector.data();
		}

		///
		/// @brief 获取底层的缓冲区
		///
		///
		/// @return
		///
		virtual ItemType const *Buffer() const override
		{
			return _vector.data();
		}

		/* #endregion */

		/* #region GetEnumerator */

		using IEnumerable<ItemType>::GetEnumerator;

		virtual std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() override
		{
			return base::IRawArray<ItemType>::GetEnumerator();
		}

		/* #endregion */

		/* #region 比较运算符 */

		using base::IRawArray<ItemType>::operator==;
		using base::IRawArray<ItemType>::operator<;
		using base::IRawArray<ItemType>::operator>;
		using base::IRawArray<ItemType>::operator<=;
		using base::IRawArray<ItemType>::operator>=;

		using IList<ItemType>::operator==;

		///
		/// @brief 转发到 std::vector 的相等判断逻辑。
		///
		/// @param another
		///
		/// @return
		///
		bool operator==(List<ItemType> const &another) const
		{
			return _vector == another._vector;
		}

		/* #endregion */
	};

} // namespace base

#pragma once
#include <base/container/iterator/IEnumerable.h>
#include <base/container/iterator/IForwardIterator.h>
#include <functional>

namespace base
{
	/// @brief 列表接口
	/// @tparam ItemType
	template <typename ItemType>
	class IList :
		public virtual base::IEnumerable<ItemType>
	{
	private:
		// 迭代器

		/**
		 * @brief 用来迭代 IList 的私有迭代器。
		 *
		 * @tparam item_type
		 */
		template <typename item_type>
		class Enumerator :
			public base::IEnumerator<item_type>
		{
		private:
			IList<item_type> *_list;
			int32_t _index = 0;
			bool _is_first_move = true;

		public:
			Enumerator(IList<item_type> *list)
			{
				_list = list;
			}

			virtual item_type &CurrentValue() override
			{
				return (*_list)[_index];
			}

			virtual bool MoveNext() override
			{
				if (_is_first_move)
				{
					_is_first_move = false;
				}
				else
				{
					_index++;
				}

				return _index < _list->Count();
			}

			virtual void Reset() override
			{
				_is_first_move = true;
				_index = 0;
			}
		};

	public:
		// 接口
		virtual void Add(ItemType const &item) = 0;
		virtual void Insert(int32_t index, ItemType const &item) = 0;
		virtual bool Remove(ItemType const &item) = 0;
		virtual void RemoveAt(int32_t index) = 0;
		virtual int32_t IndexOf(ItemType const &item) const = 0;
		virtual bool Contains(ItemType const &item) const = 0;
		virtual void Clear() = 0;
		virtual int32_t Count() const = 0;
		virtual ItemType &operator[](int32_t index) = 0;
		virtual ItemType const &operator[](int32_t index) const = 0;

		/**
		 * @brief 移除符合条件的数据。
		 *
		 * @param should_remove 用来指示特定的元素是否应该从容器中移除。
		 */
		virtual void RemoveIf(std::function<bool(ItemType const &item)> should_remove) = 0;

	public:
		virtual void Add(IList<ItemType> const &list)
		{
			for (ItemType const &item : list)
			{
				Add(item);
			}
		}

		virtual void Add(std::initializer_list<ItemType> const &list)
		{
			for (ItemType const &item : list)
			{
				Add(item);
			}
		}

		/// @brief 获取迭代器
		/// @return
		virtual std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() override
		{
			return std::shared_ptr<IEnumerator<ItemType>>{new Enumerator<ItemType>{this}};
		}

		/// @brief 两个 IList 对象的指针相等时才认为相等。
		/// @param o
		/// @return
		bool operator==(IList<ItemType> const &o) const
		{
			return this == &o;
		}
	};
} // namespace base

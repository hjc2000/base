#pragma once
#include <algorithm>
#include <array>
#include <base/container/iterator/IEnumerable.h>
#include <base/container/iterator/IForwardIterator.h>

namespace base
{
	/// @brief 列表接口
	/// @tparam ItemType
	template <typename ItemType>
	class IList :
		virtual public base::IEnumerable<ItemType>
	{
	private:
#pragma region IListEnumerator

		template <typename item_type>
		class IListEnumerator :
			public base::IEnumerator<item_type>
		{
		private:
			IList<item_type> *_list;
			int32_t _index = 0;
			bool _is_first_move = true;

		public:
			IListEnumerator(IList<item_type> *list)
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

#pragma endregion

	public:
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
			return std::shared_ptr<IEnumerator<ItemType>>{new IListEnumerator<ItemType>{this}};
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

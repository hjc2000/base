#pragma once
#include <array>
#include <base/container/ICollection.h>
#include <base/container/IIterator.h>

namespace base
{
	template <typename ItemType>
	class IList
		: public ICollection<int, ItemType>
	{
	public:
		virtual ~IList() = default;

		ItemType Get(int key) const override
		{
			return (*this)[key];
		}

		void Put(int key, ItemType const &item) override
		{
			(*this)[key] = item;
		}

		virtual void Add(ItemType const &item) = 0;

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

		virtual void Insert(int index, ItemType const &item) = 0;
		virtual bool Remove(ItemType const &item) = 0;
		virtual void RemoveAt(int index) = 0;
		virtual int IndexOf(ItemType const &item) const = 0;
		virtual bool Contains(ItemType const &item) const = 0;
		virtual void Clear() = 0;
		virtual int Count() const = 0;
		virtual ItemType &operator[](int index) = 0;
		virtual ItemType const &operator[](int index) const = 0;

#pragma region 迭代器
		template <typename ItItemType, typename ListType>
		class IListIterator
			: public base::IForwardIterator<IListIterator<ItItemType, ListType>, ItItemType>
		{
		private:
			ListType *_list;
			int _index;

		public:
			IListIterator(ListType *list, int index)
				: _list(list),
				  _index(index)
			{
			}

			ItItemType &operator*() override
			{
				return (*_list)[_index];
			}

			using base::IForwardIterator<IListIterator<ItItemType, ListType>, ItItemType>::operator++;

			IListIterator<ItItemType, ListType> &operator++() override
			{
				++_index;
				return *this;
			}

			bool operator==(IListIterator<ItItemType, ListType> const &o) const override
			{
				return _index == o._index;
			}
		};

		IListIterator<ItemType, IList<ItemType>> begin()
		{
			return IListIterator<ItemType, IList<ItemType>>(this, 0);
		}

		IListIterator<ItemType, IList<ItemType>> end()
		{
			return IListIterator<ItemType, IList<ItemType>>(this, Count());
		}

		IListIterator<ItemType const, IList<ItemType> const> begin() const
		{
			return IListIterator<ItemType const, IList<ItemType> const>(this, 0);
		}

		IListIterator<ItemType const, IList<ItemType> const> end() const
		{
			return IListIterator<ItemType const, IList<ItemType> const>(this, Count());
		}
#pragma endregion

		/// @brief 两个 IList 对象的指针相等时才认为相等。
		/// @param another
		/// @return
		bool operator==(IList<ItemType> const &another) const
		{
			return this == &another;
		}
	};
}

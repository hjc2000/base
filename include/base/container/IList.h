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
		class IListIterator
			: public base::IForwardIterator<IListIterator, ItemType>
		{
		private:
			IList<ItemType> *_list;
			int _index;

		public:
			IListIterator(IList<ItemType> *list, int index)
				: _list(list),
				  _index(index)
			{
			}

			ItemType &operator*() override
			{
				return (*_list)[_index];
			}

			using base::IForwardIterator<IListIterator, ItemType>::operator++;

			IListIterator &operator++() override
			{
				++_index;
				return *this;
			}

			bool operator==(IListIterator const &o) const override
			{
				return _index == o._index;
			}
		};

		IListIterator begin()
		{
			return IListIterator(this, 0);
		}

		IListIterator end()
		{
			return IListIterator(this, Count());
		}
#pragma endregion

#pragma region const迭代器
		class IListConstIterator
		{
		private:
			IList<ItemType> const *_list;
			int _index;

		public:
			IListConstIterator(IList<ItemType> const *list, int index)
				: _list(list),
				  _index(index)
			{
			}

			ItemType const &operator*()
			{
				return (*_list)[_index];
			}

			IListConstIterator &operator++()
			{
				++_index;
				return *this;
			}

			bool operator!=(IListConstIterator const &other) const
			{
				return _index != other._index;
			}
		};

		IListConstIterator begin() const
		{
			return IListConstIterator(this, 0);
		}

		IListConstIterator end() const
		{
			return IListConstIterator(this, Count());
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

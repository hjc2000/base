#pragma once
#include <array>
#include <base/container/ICollection.h>
#include <base/container/IIterator.h>
#include <base/sfinae/IsConst.h>
#include <base/sfinae/TypeSelector.h>

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
		template <typename ItItemType>
		class IListIterator
			: public base::IForwardIterator<IListIterator<ItItemType>, ItItemType>
		{
		private:
			/// @brief 类型选择器，用来选择迭代器持有的是 IList<ItemType> const 还是
			/// IList<ItemType> 类型的列表。
			///
			/// IList<ItemType> 中 const 版本的 begin 函数中将 this 指针传递给本迭代器的构造函数，
			/// const 版本的 begin 中的 this 指针是 IList<ItemType> const * 类型，也就是说此时
			/// 本迭代器会持有一个 const 容器，这个容器无法增删，容器内的元素也是 const 的，也就无法
			/// 改。
			///
			/// 为了让本迭代器类的构造函数适应 IList<ItemType> const * 和 IList<ItemType> * ，
			/// 并在不同情况下让本类的 _list 字段是这两种类型，需要利用模板元编程来确定 _list 的
			/// 类型。
			using ListType = typename base::TypeSelector<base::IsConstType<ItItemType>(),
														 IList<ItemType> const,
														 IList<ItemType>>::Type;

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

			using base::IForwardIterator<IListIterator<ItItemType>, ItItemType>::operator++;

			IListIterator<ItItemType> &operator++() override
			{
				++_index;
				return *this;
			}

			bool operator==(IListIterator<ItItemType> const &o) const override
			{
				return _index == o._index;
			}
		};

		IListIterator<ItemType> begin()
		{
			return IListIterator<ItemType>(this, 0);
		}

		IListIterator<ItemType> end()
		{
			return IListIterator<ItemType>(this, Count());
		}

		IListIterator<ItemType const> begin() const
		{
			return IListIterator<ItemType const>(this, 0);
		}

		IListIterator<ItemType const> end() const
		{
			return IListIterator<ItemType const>(this, Count());
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

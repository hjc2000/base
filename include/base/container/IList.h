#pragma once
#include <array>
#include <base/container/ICollection.h>
#include <base/container/IEnumerable.h>
#include <base/container/IIterator.h>
#include <base/container/StdContainerEnumerable.h>
#include <base/sfinae/IsConst.h>
#include <base/sfinae/TypeSelector.h>

namespace base
{
	template <typename ItemType>
	class IList
		: public ICollection<int, ItemType>,
		  public base::IEnumerable<ItemType>
	{
	private:
		template <typename IListEnumeratorItemType>
		class IListEnumerator
			: public base::IEnumerator<IListEnumeratorItemType>
		{
		private:
			IList<IListEnumeratorItemType> *_list;
			int _index = 0;
			bool _is_first_move = true;

		public:
			IListEnumerator(IList<IListEnumeratorItemType> *list)
			{
				_list = list;
			}

			IListEnumeratorItemType &CurrentValue() override
			{
				return (*_list)[_index];
			}

			bool MoveNext() override
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

			void Reset() override
			{
				_index = 0;
			}
		};

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
		std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() override
		{
			return std::shared_ptr<IEnumerator<ItemType>>{new IListEnumerator<ItemType>{this}};
		}

		std::shared_ptr<IEnumerator<ItemType const>> GetEnumerator() const override
		{
			return std::shared_ptr<IEnumerator<ItemType>>{new IListEnumerator<ItemType>{const_cast<IList<ItemType>>(this)}};
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

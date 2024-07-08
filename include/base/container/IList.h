#pragma once

namespace base
{
	template <typename T>
	class IList
	{
	public:
		virtual ~IList() = default;

		virtual void Add(T const &item) = 0;

		virtual void Add(IList<T> &list)
		{
			for (T &item : list)
			{
				Add(item);
			}
		}

		virtual void Insert(int index, T const &item) = 0;
		virtual bool Remove(T const &item) = 0;
		virtual void RemoveAt(int index) = 0;
		virtual int IndexOf(T const &item) const = 0;
		virtual bool Contains(T const &item) const = 0;
		virtual void Clear() = 0;
		virtual int Count() const = 0;
		virtual T &operator[](int index) = 0;
		virtual T const &operator[](int index) const = 0;

#pragma region 迭代器
		class IListIterator
		{
		private:
			IList<T> *_list;
			int _index;

		public:
			IListIterator(IList<T> *list, int index)
				: _list(list),
				  _index(index)
			{
			}

			T &operator*()
			{
				return (*_list)[_index];
			}

			IListIterator &operator++()
			{
				++_index;
				return *this;
			}

			bool operator!=(IListIterator const &other) const
			{
				return _index != other._index;
			}
		};

		class IListConstIterator
		{
		private:
			IList<T> const *_list;
			int _index;

		public:
			IListConstIterator(IList<T> const *list, int index)
				: _list(list),
				  _index(index)
			{
			}

			T const &operator*()
			{
				return (*_list)[_index];
			}

			IListIterator &operator++()
			{
				++_index;
				return *this;
			}

			bool operator!=(IListIterator const &other) const
			{
				return _index != other._index;
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
		bool operator==(IList<T> const &another) const
		{
			return this == &another;
		}
	};
}

#pragma once

namespace base
{
	/// @brief 迭代器接口。
	/// @tparam TypeSelf 本接口的派生类将 TypeSelf 设置为自己的类型。
	/// @tparam ItemType 被迭代元素的类型。
	template <typename TypeSelf, typename ItemType>
	class IForwardIterator
	{
	public:
		/// @brief 解引用
		/// @return
		virtual ItemType &operator*() = 0;

		/// @brief 前缀递增
		/// @return
		virtual TypeSelf &operator++() = 0;

		virtual bool operator==(TypeSelf const &o) const = 0;

#pragma region 扩展
		/// @brief 后缀递增
		/// @param
		/// @return
		virtual TypeSelf &operator++(int)
		{
			return operator++();
		}

		ItemType *operator->()
		{
			return &operator*();
		}

		bool operator!=(TypeSelf const &o) const
		{
			return !(*this == o);
		}
#pragma endregion
	};

	/// @brief 迭代器接口
	/// @tparam ItemType
	template <typename ItemType>
	class IEnumerator
	{
	public:
		virtual ItemType CurrentValue() = 0;
		virtual bool MoveNext() = 0;
		virtual void Reset() = 0;
	};

	/// @brief 将 IEnumerator 包装为 C++ 迭代器
	/// @tparam ItemType
	template <typename ItemType>
	class IEnumeratorForwardIterator
		: public IForwardIterator<IEnumeratorForwardIterator<ItemType>, ItemType>
	{
	private:
		IEnumerator<ItemType> &_enumertor;

	public:
		IEnumeratorForwardIterator(IEnumerator<ItemType> &enumertor)
			: _enumertor(_enumertor)
		{
			_enumertor.MoveNext();
		}

		/// @brief 解引用
		/// @return
		ItemType &operator*()
		{
			return _enumertor.CurrentValue();
		}

		/// @brief 前缀递增
		/// @return
		IEnumeratorForwardIterator<ItemType> &operator++()
		{
			return *this;
		}

		bool operator==(IEnumeratorForwardIterator<ItemType> const &o) const
		{
			return !_enumertor.MoveNext();
		}
	};

	/// @brief 可迭代容器接口。
	/// @tparam ItemType
	template <typename ItemType>
	class IEnumerable
	{
	public:
		virtual IEnumerator<ItemType> GetEnumerator() = 0;
	};
}

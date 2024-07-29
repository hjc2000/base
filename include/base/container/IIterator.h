#pragma once
#include <memory>

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
		virtual ItemType &CurrentValue() = 0;
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
		std::shared_ptr<IEnumerator<ItemType>> _enumertor;

	public:
		IEnumeratorForwardIterator(std::shared_ptr<IEnumerator<ItemType>> enumertor)
		{
			_enumertor = enumertor;
		}

		/// @brief 解引用
		/// @return
		ItemType &operator*()
		{
			return _enumertor->CurrentValue();
		}

		/// @brief 前缀递增
		/// @return
		IEnumeratorForwardIterator<ItemType> &operator++()
		{
			// 不做任何操作，因为 == 运算符里面已经 MoveNext 了。
			return *this;
		}

		bool operator==(IEnumeratorForwardIterator<ItemType> const &o) const
		{
			/* C++ 范围 for 的机制是先判断不等于 end() 然后解引用。然后递增，进入下一循环。
			 * IEnumerator 的操作顺序是先 MoveNext 然后判断是否成功，成功再利用 CurrentValue
			 * 获取引用。
			 *
			 * 让 == 运算符返回 !_enumertor->MoveNext()，这样，范围 for 的判断不等于 end() 的
			 * 步骤就会触发移动，并得到是否移动成功的结果，移动失败，就返回 true ，让范围 for 认为
			 * 当前等于 end() ，于是结束迭代。
			 */
			return !_enumertor->MoveNext();
		}
	};

	/// @brief 可迭代容器接口。
	/// @tparam ItemType
	template <typename ItemType>
	class IEnumerable
	{
	public:
		virtual std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() = 0;

		IEnumeratorForwardIterator<ItemType> begin()
		{
			return IEnumeratorForwardIterator<ItemType>{GetEnumerator()};
		}

		IEnumeratorForwardIterator<ItemType> end()
		{
			return IEnumeratorForwardIterator<ItemType>{GetEnumerator()};
		}
	};

	class IntEnumerator
		: public IEnumerator<int>
	{
	private:
		int _value = 0;
		bool _is_first_move = true;

	public:
		int &CurrentValue() override
		{
			return _value;
		}

		bool MoveNext()
		{
			if (_is_first_move)
			{
				_is_first_move = false;
			}
			else
			{
				_value++;
			}

			if (_value >= 10)
			{
				return false;
			}

			return true;
		}

		void Reset() override
		{
			_value = 0;
		}
	};

	class IntEnumerable
		: public IEnumerable<int>
	{
	public:
		std::shared_ptr<IEnumerator<int>> GetEnumerator() override
		{
			return std::shared_ptr<IEnumerator<int>>{new IntEnumerator{}};
		}
	};

	void TestIntEnumerable();
}

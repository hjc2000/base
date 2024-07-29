#pragma once
#include <base/container/IEnumerator.h>
#include <base/container/IEnumeratorForwardIterator.h>
#include <base/container/IIterator.h>
#include <memory>

namespace base
{
	/// @brief 可迭代容器接口。
	/// @tparam ItemType
	template <typename ItemType>
	class IEnumerable
	{
	public:
		virtual std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() = 0;
		virtual std::shared_ptr<IEnumerator<ItemType const>> GetEnumerator() const = 0;

		IEnumeratorForwardIterator<ItemType> begin()
		{
			return IEnumeratorForwardIterator<ItemType>{GetEnumerator()};
		}

		IEnumeratorForwardIterator<ItemType> end()
		{
			return IEnumeratorForwardIterator<ItemType>{GetEnumerator()};
		}

		IEnumeratorForwardIterator<ItemType const> begin() const
		{
			return IEnumeratorForwardIterator<ItemType const>{GetEnumerator()};
		}

		IEnumeratorForwardIterator<ItemType const> end() const
		{
			return IEnumeratorForwardIterator<ItemType const>{GetEnumerator()};
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

	class ConstIntEnumerator
		: public IEnumerator<int const>
	{
	private:
		int _value = 0;
		bool _is_first_move = true;

	public:
		int const &CurrentValue() override
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

		std::shared_ptr<IEnumerator<int const>> GetEnumerator() const override
		{
			return std::shared_ptr<IEnumerator<int const>>{new ConstIntEnumerator{}};
		}
	};

	void TestIntEnumerable();
}
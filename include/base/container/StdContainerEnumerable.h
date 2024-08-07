#pragma once
#ifndef HAS_THREAD
#define HAS_THREAD 0
#endif

#include <base/container/IEnumerable.h>
#include <memory>

namespace base
{
	// C++ 迭代器类要满足的要求。
	template <typename T>
	concept IsIterator = requires(T &c) {
		c++;
		c == c;
		*c;
	};

	/// @brief 将 std 容器的迭代器包装为 IEnumerator。
	/// @tparam ItemType 被迭代元素的类型。
	/// @tparam IteratorType 迭代器类型。
	template <typename ItemType, IsIterator IteratorType>
	class StdContainerEnumerator final
		: public base::IEnumerator<ItemType>
	{
	private:
		IteratorType _current_iterator;
		IteratorType _begin_iterator;
		IteratorType _end_iterator;
		bool _is_first_move = true;

	public:
		StdContainerEnumerator(IteratorType begin_iterator, IteratorType end_iterator)
		{
			_current_iterator = begin_iterator;
			_begin_iterator = begin_iterator;
			_end_iterator = end_iterator;
		}

		ItemType &CurrentValue() override
		{
			return *_current_iterator;
		}

		bool MoveNext() override
		{
			if (_is_first_move)
			{
				_is_first_move = false;
			}
			else
			{
				_current_iterator++;
			}

			if (_current_iterator == _end_iterator)
			{
				// 移动到下一个元素失败
				return false;
			}

			// 移动到下一个元素成功
			return true;
		}

		void Reset() override
		{
			_current_iterator = _begin_iterator;
		}
	};

	// C++ 可迭代容器要满足的条件。
	template <typename T>
	concept IsIterable = requires(T &c) {
		c.begin();
		c.end();
	};

	/// @brief 将 std 容器包装为 IEnumerable
	/// @tparam ItemType 被迭代元素的类型
	/// @tparam ContainerType 容器类型
	template <typename ItemType, IsIterable ContainerType>
	class StdContainerEnumerable final
		: public IEnumerable<ItemType>
	{
	private:
		std::shared_ptr<ContainerType> _container;

	public:
		StdContainerEnumerable(std::shared_ptr<ContainerType> container)
		{
			_container = container;
		}

		std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() override
		{
			return std::shared_ptr<IEnumerator<ItemType>>{
				new StdContainerEnumerator<ItemType, decltype(_container->begin())>{
					_container->begin(),
					_container->end(),
				},
			};
		}
	};

#if HAS_THREAD
	void TestStdContainerEnumerable();
#endif
}

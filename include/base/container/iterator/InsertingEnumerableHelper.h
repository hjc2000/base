#pragma once
#include "base/container/iterator/IEnumerable.h"
#include <cstdint>

namespace base
{
	template <typename ItemType>
	class InsertingEnumerableHelper
	{
	public:
		class Iterator
		{
		private:
			int64_t _count = 0;
			std::shared_ptr<base::IEnumerator<ItemType const>> _enumerator;

		public:
			Iterator() = default;

			///
			/// @brief
			///
			/// @param enumerator 迭代器。
			/// @param count 总共可迭代多少个元素。
			///
			Iterator(std::shared_ptr<base::IEnumerator<ItemType const>> const &enumerator, int64_t count)
				: _enumerator(enumerator),
				  _count(count)
			{
			}

			ItemType const &operator*()
			{
				return _enumerator->CurrentValue();
			}

			ItemType const *operator->()
			{
				return &operator*();
			}

			///
			/// @brief 前缀递增
			///
			/// @return
			///
			Iterator &operator++()
			{
				_count--;
				_enumerator->Add();
				return *this;
			}

			int64_t operator-(Iterator const &other) const
			{
				if (_enumerator == other._enumerator)
				{
					// 两者指向同一个对象，无论如何都是相等的。
					return 0;
				}

				if (_enumerator != nullptr && other._enumerator == nullptr)
				{
					// 本对象不是 end, other 是 end.
					// this - end = -_count
					return -_count;
				}

				if (_enumerator == nullptr && other._enumerator != nullptr)
				{
					// 本对象是 end, other 不是 end.
					// end - other = _count
					return other._count;
				}

				if (_enumerator != nullptr && other._enumerator != nullptr)
				{
					return _count - other._count;
				}

				if (_enumerator == nullptr && other._enumerator == nullptr)
				{
					return 0;
				}

				return 0;
			}

			bool operator==(Iterator const &other) const
			{
				if (_enumerator == other._enumerator)
				{
					// 两者指向同一个对象，无论如何都是相等的。
					return true;
				}

				if (_enumerator != nullptr && other._enumerator == nullptr)
				{
					// 本对象不是 end, other 是 end.
					return _enumerator->IsEnd();
				}

				if (_enumerator == nullptr && other._enumerator != nullptr)
				{
					// 本对象是 end, other 不是 end.
					return other._enumerator->IsEnd();
				}

				if (_enumerator != nullptr && other._enumerator != nullptr)
				{
					// 两个的 _enumerator 指向不同对象，分别独立迭代，则比较 _count 计数
					// 来判断是不是迭代到相同的位置了。
					return _count == other._count;
				}

				if (_enumerator == nullptr && other._enumerator == nullptr)
				{
					return true;
				}

				return true;
			}

			bool operator!=(Iterator const &other) const
			{
				return !(*this == other);
			}
		};

	private:
		base::IEnumerable<ItemType> const &_enumerable;
		int64_t _count = 0;

	public:
		InsertingEnumerableHelper(base::IEnumerable<ItemType> const &enumerable, int64_t count)
			: _enumerable(enumerable),
			  _count(count)
		{
		}

		Iterator begin() const
		{
			return Iterator{_enumerable.GetEnumerator(), _count};
		}

		Iterator end() const
		{
			return Iterator{};
		}
	};

} // namespace base

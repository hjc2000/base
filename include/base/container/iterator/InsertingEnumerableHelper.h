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

			///
			/// @brief 后缀递增。
			///
			/// @return
			///
			Iterator operator++(int)
			{
				Iterator ret{*this};
				++(*this);
				return ret;
			}

			int64_t operator-(Iterator const &other) const
			{
				if (_enumerator == nullptr)
				{
					// 本对象是 end, end - other = count
					return other._count;
				}

				if (other._enumerator == nullptr)
				{
					// other 是 end 而本对象不是。
					// this - end = -_count
					return -_count;
				}

				return 0;
			}

			bool operator==(Iterator const &other) const
			{
				if (_enumerator != nullptr)
				{
					// 本对象不是 end.
					if (_count <= 0)
					{
						return true;
					}

					return _enumerator->IsEnd();
				}

				if (other._enumerator != nullptr)
				{
					// 本对象是 end 而 other 不是。
					if (other._count <= 0)
					{
						return true;
					}

					return other._enumerator->IsEnd();
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

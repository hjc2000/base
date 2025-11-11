#pragma once
#include "base/container/iterator/IEnumerable.h"
#include "base/container/Range.h"
#include "base/string/define.h"
#include <cstdint>
#include <stdexcept>

namespace base
{
	///
	/// @brief 只读的数组内存段。
	///
	/// @note 引用一段内存，不会持有这段内存，不管理这段内存的生命周期。
	///
	template <typename ItemType>
	class ReadOnlyArraySpan final :
		public base::IEnumerable<ItemType const>
	{
	private:
		/* #region 迭代器 */

		class Enumerator :
			public base::IEnumerator<ItemType const>
		{
		private:
			int64_t _index = 0;
			ItemType const *_buffer{};
			int64_t _count = 0;
			bool _has_not_moved = true;

		public:
			Enumerator(ItemType const *buffer, int64_t count)
			{
				_buffer = buffer;
				_count = count;
			}

			///
			/// @brief 迭代器当前是否指向尾后元素。
			///
			/// @return
			///
			virtual bool IsEnd() const override
			{
				return _index == _count;
			}

			///
			/// @brief 获取当前值的引用。
			///
			/// @return ItemType&
			///
			virtual ItemType const &CurrentValue() override
			{
				return _buffer[_index];
			}

			///
			/// @brief 递增迭代器的位置。
			///
			///
			virtual void Add() override
			{
				++_index;
			}

			///
			/// @brief 从未被调用过 MoveToNext 方法。
			///
			/// @return
			///
			virtual bool HasNotMoved() override
			{
				return _has_not_moved;
			}

			///
			/// @brief 设置是否从未被调用过 MoveToNext 方法。
			///
			/// @param value
			///
			virtual void SetHasNotMoved(bool value) override
			{
				_has_not_moved = value;
			}
		};

		/* #endregion */

		ItemType const *_buffer = nullptr;
		int64_t _count = 0;

	public:
		/* #region 构造函数 */

		///
		/// @brief 构造函数。构造出来的对象不会引用任何有效内存段，且大小为 0.
		///
		///
		ReadOnlyArraySpan() = default;

		///
		/// @brief 构造函数。
		///
		/// @param buffer 要引用的内存段指针。
		/// @param count 要引用的内存段大小。
		///
		ReadOnlyArraySpan(ItemType const *buffer, int64_t count)
		{
			_buffer = buffer;
			_count = count;

			if (_buffer == nullptr)
			{
				_count = 0;
			}
		}

		/* #endregion */

		///
		/// @brief 获取本对象引用的内存段。
		///
		/// @return
		///
		ItemType const *Buffer() const
		{
			return _buffer;
		}

		///
		/// @brief 本对象引用的内存段的元素个数。
		///
		/// @return
		///
		int64_t Count() const
		{
			return _count;
		}

		base::ReadOnlyArraySpan<ItemType> Slice(base::Range const &range) const
		{
			if (range.End() > Count())
			{
				throw std::out_of_range{"超出范围，无法切片。"};
			}

			return base::ReadOnlyArraySpan<ItemType>{Buffer() + range.Begin(), range.Size()};
		}

		base::ReadOnlyArraySpan<ItemType> operator[](base::Range const &range) const
		{
			return Slice(range);
		}

		ItemType const &Get(int64_t index) const
		{
			if (index < 0 || index >= Count())
			{
				throw std::out_of_range{CODE_POS_STR + "index 参数超出范围。"};
			}

			return Buffer()[index];
		}

		ItemType const &operator[](int64_t index) const
		{
			return Get(index);
		}

		/* #region GetEnumerator */

		using base::IEnumerable<ItemType const>::GetEnumerator;

		///
		/// @brief 获取迭代器。
		///
		/// @return
		///
		std::shared_ptr<IEnumerator<ItemType const>> GetEnumerator() override
		{
			return std::shared_ptr<IEnumerator<ItemType const>>{new Enumerator{Buffer(), Count()}};
		}

		/* #endregion */
	};

} // namespace base

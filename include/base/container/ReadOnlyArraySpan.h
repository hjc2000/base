#pragma once
#include "base/container/Range.h"
#include "base/stream/ReadOnlySpan.h"
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
	class ReadOnlyArraySpan final
	{
	private:
	public:
		/* #region 迭代器 */

		template <typename item_type>
		class Iterator
		{
		private:
			ReadOnlyArraySpan *_span = nullptr;
			int64_t _index = 0;

		public:
			using iterator_category = std::random_access_iterator_tag;
			using value_type = item_type;
			using difference_type = int64_t;
			using pointer = item_type *;
			using reference = item_type &;

			Iterator() = default;

			Iterator(ReadOnlyArraySpan *span, int64_t index)
			{
				_span = span;
				_index = index;
			}

			item_type &operator*()
			{
				if (_span == nullptr)
				{
					throw std::invalid_argument{CODE_POS_STR + "迭代器处于无效状态。"};
				}

				return (*_span)[_index];
			}

			item_type *operator->()
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
				_index++;
				return *this;
			}

			///
			/// @brief 后缀递增。
			///
			Iterator operator++(int)
			{
				Iterator copy{*this};
				_index++;
				return copy;
			}

			///
			/// @brief 前缀递减。
			///
			/// @return
			///
			Iterator &operator--()
			{
				_index--;
				return *this;
			}

			///
			/// @brief 后缀递减。
			///
			/// @return
			///
			Iterator operator--(int)
			{
				Iterator copy{*this};
				_index--;
				return copy;
			}

			Iterator &operator+=(int64_t value)
			{
				_index += value;
				return *this;
			}

			Iterator operator+(int64_t value) const
			{
				Iterator copy{*this};
				copy += value;
				return copy;
			}

			int64_t operator-(Iterator const &other) const
			{
				return _index - other._index;
			}

			bool operator==(Iterator const &other) const
			{
				return _index == other._index;
			}

			bool operator!=(Iterator const &other) const
			{
				return !(*this == other);
			}
		};

		/* #endregion */

	private:
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

		operator base::ReadOnlySpan() const
			requires(std::is_same_v<ItemType, uint8_t>)
		{
			return base::ReadOnlySpan{Buffer(), Count()};
		}

		/* #region 迭代 */

		Iterator<ItemType> begin()
		{
			return Iterator<ItemType>{this, 0};
		}

		Iterator<ItemType> end()
		{
			return Iterator<ItemType>{this, Count()};
		}

		Iterator<ItemType const> begin() const
		{
			return Iterator<ItemType const>{const_cast<ReadOnlyArraySpan *>(this), 0};
		}

		Iterator<ItemType const> end() const
		{
			return Iterator<ItemType const>{const_cast<ReadOnlyArraySpan *>(this), Count()};
		}

		/* #endregion */
	};

} // namespace base

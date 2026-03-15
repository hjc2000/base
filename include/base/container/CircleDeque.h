#pragma once
#include "base/math/Counter.h"
#include "base/string/define.h"
#include "IDeque.h"
#include <algorithm>
#include <cstdint>
#include <stdexcept>

namespace base
{
	///
	/// @brief 循环缓冲区的双端队列。
	///
	template <typename ItemType, int64_t Size>
		requires(Size > 0)
	class CircleDeque final :
		public base::IDeque<ItemType>
	{
	private:
	public:
		/* #region 迭代器 */

		template <typename item_type>
		class Iterator
		{
		private:
			CircleDeque *_span = nullptr;
			int64_t _index = 0;

		public:
			using iterator_category = std::random_access_iterator_tag;
			using value_type = item_type;
			using difference_type = int64_t;
			using pointer = item_type *;
			using reference = item_type &;

			Iterator() = default;

			Iterator(CircleDeque *span, int64_t index)
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
		alignas(ItemType) uint8_t _memory_block[sizeof(ItemType) * Size]{};
		base::Counter<uint64_t> _begin{0, Size - 1};
		base::Counter<uint64_t> _end{0, Size - 1};
		bool _is_full = false;

		ItemType *Buffer()
		{
			return reinterpret_cast<ItemType *>(_memory_block);
		}

		ItemType const *Buffer() const
		{
			return reinterpret_cast<ItemType const *>(_memory_block);
		}

	public:
		~CircleDeque()
		{
			Clear();
		}

		///
		/// @brief 队列中当前元素的数量。
		///
		/// @return
		///
		virtual int64_t Count() const override
		{
			if (_is_full)
			{
				return Size;
			}

			return _end - _begin;
		}

		bool IsFull() const
		{
			return _is_full;
		}

		///
		/// @brief 队列的容纳能力。即最多容纳多少个元素。
		///
		/// @return
		///
		int64_t Capacity() const
		{
			return Size;
		}

		///
		/// @brief 从队列末端入队。
		///
		/// @param obj
		///
		virtual void PushBack(ItemType const &obj) override
		{
			if (_is_full)
			{
				throw std::runtime_error{CODE_POS_STR + "队列已满，无法入队。"};
			}

			new (&Buffer()[_end.Value()]) ItemType{obj};
			_end++;
			if (_begin == _end)
			{
				_is_full = true;
			}
		}

		///
		/// @brief 从队列前端入队。
		///
		/// @param obj
		///
		virtual void PushFront(ItemType const &obj) override
		{
			if (_is_full)
			{
				throw std::runtime_error{CODE_POS_STR + "队列已满，无法入队。"};
			}

			_begin--;

			try
			{
				new (&Buffer()[_begin.Value()]) ItemType{obj};
				if (_begin == _end)
				{
					_is_full = true;
				}
			}
			catch (...)
			{
				// 回滚
				_begin++;
				throw;
			}
		}

		///
		/// @brief 丢弃末尾的元素。
		///
		virtual void DiscardBack() override
		{
			if (Count() == 0)
			{
				return;
			}

			_end--;
			_is_full = false;
			Buffer()[_end.Value()].~ItemType();
		}

		///
		/// @brief 从队列末端退队。
		///
		/// @return
		///
		virtual ItemType PopBack() override
		{
			if (Count() == 0)
			{
				throw std::runtime_error{CODE_POS_STR + "队列为空，无法退队。"};
			}

			_end--;
			_is_full = false;
			ItemType ret{std::move(Buffer()[_end.Value()])};
			Buffer()[_end.Value()].~ItemType();
			return ret;
		}

		///
		/// @brief 尝试从队列末端退队。
		///
		virtual void TryPopBack(base::Placement<ItemType> &placement) override
		{
			if (Count() == 0)
			{
				return;
			}

			_end--;
			_is_full = false;
			placement = std::move(Buffer()[_end.Value()]);
			Buffer()[_end.Value()].~ItemType();
		}

		///
		/// @brief 丢弃队列前端的元素。
		///
		virtual void DiscardFront() override
		{
			if (Count() == 0)
			{
				return;
			}

			int64_t index = _begin.Value();
			Buffer()[index].~ItemType();
			_begin++;
			_is_full = false;
		}

		///
		/// @brief 从队列前端退队。
		///
		/// @return
		///
		virtual ItemType PopFront() override
		{
			if (Count() == 0)
			{
				throw std::runtime_error{CODE_POS_STR + "队列为空，无法退队。"};
			}

			int64_t index = _begin.Value();
			ItemType ret{std::move(Buffer()[index])};
			Buffer()[index].~ItemType();
			_begin++;
			_is_full = false;
			return ret;
		}

		///
		/// @brief 尝试从队列前端退队。
		///
		virtual void TryPopFront(base::Placement<ItemType> &placement) override
		{
			if (Count() == 0)
			{
				return;
			}

			int64_t index = _begin.Value();
			placement = std::move(Buffer()[index]);
			Buffer()[index].~ItemType();
			_begin++;
			_is_full = false;
		}

		///
		/// @brief 清空队列。
		///
		///
		virtual void Clear() override
		{
			for (int64_t i = 0; i < Count(); i++)
			{
				Get(i).~ItemType();
			}

			_begin.Reset();
			_end.Reset();
			_is_full = false;
		}

		/* #region 索引器 */

		///
		/// @brief 获取队列最前端的元素。
		///
		/// @return
		///
		ItemType &Front()
		{
			return Get(0);
		}

		///
		/// @brief 获取队列最前端的元素。
		///
		/// @return
		///
		ItemType const &Front() const
		{
			return Get(0);
		}

		///
		/// @brief 获取队列最末尾的元素。
		///
		/// @return
		///
		ItemType &Back()
		{
			return Get(Count() - 1);
		}

		///
		/// @brief 获取队列最末尾的元素。
		///
		/// @return
		///
		ItemType const &Back() const
		{
			return Get(Count() - 1);
		}

		///
		/// @brief 获取指定索引的元素。
		///
		/// @param index
		/// @return
		///
		ItemType &Get(int64_t index)
		{
			if (index < 0 || index >= Count())
			{
				throw std::out_of_range{CODE_POS_STR + "索引越界。"};
			}

			int64_t real_index = _begin + index;
			return Buffer()[real_index];
		}

		///
		/// @brief 获取指定索引的元素。
		///
		/// @param index
		/// @return
		///
		ItemType const &Get(int64_t index) const
		{
			if (index < 0 || index >= Count())
			{
				throw std::out_of_range{CODE_POS_STR + "索引越界。"};
			}

			int64_t real_index = _begin + index;
			return Buffer()[real_index];
		}

		///
		/// @brief 设置指定索引的元素。
		///
		/// @param index
		/// @param value
		///
		void Set(int64_t index, ItemType const &value)
		{
			if (index < 0 || index >= Count())
			{
				throw std::out_of_range{CODE_POS_STR + "索引越界。"};
			}

			int64_t real_index = _begin + index;
			Buffer()[real_index] = value;
		}

		///
		/// @brief 获取指定索引的元素。
		///
		/// @param index
		/// @return
		///
		ItemType &operator[](int64_t index)
		{
			return Get(index);
		}

		///
		/// @brief 获取指定索引的元素。
		///
		/// @param index
		/// @return
		///
		ItemType const &operator[](int64_t index) const
		{
			return Get(index);
		}

		/* #endregion */

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
			return Iterator<ItemType const>{const_cast<CircleDeque *>(this), 0};
		}

		Iterator<ItemType const> end() const
		{
			return Iterator<ItemType const>{const_cast<CircleDeque *>(this), Count()};
		}

		/* #endregion */
	};

} // namespace base

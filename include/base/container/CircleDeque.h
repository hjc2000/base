#pragma once
#include "base/container/iterator/IRandomAccessEnumerable.h"
#include "base/container/iterator/IRandomAccessEnumerator.h"
#include "base/math/Counter.h"
#include "base/string/define.h"
#include "IDeque.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <stdexcept>

namespace base
{
	///
	/// @brief 循环缓冲区的双端队列。
	///
	///
	template <typename ItemType, int64_t Size>
		requires(Size > 0)
	class CircleDeque final :
		public base::IDeque<ItemType>,
		public base::IRandomAccessEnumerable<ItemType>
	{
	private:
		/* #region Enumerator */

		class RandomAccessEnumerator final :
			public base::IRandomAccessEnumerator<ItemType>
		{
		private:
			CircleDeque<ItemType, Size> *_queue;
			int64_t _index = 0;
			base::IEnumerator<ItemType>::Context_t _context{};

		public:
			RandomAccessEnumerator(CircleDeque<ItemType, Size> &queue)
			{
				_queue = &queue;
			}

			///
			/// @brief 克隆一个迭代器对象副本。
			///
			/// @note 派生类要实现拷贝构造函数后在这里调用自己的拷贝构造函数拷贝一份自己。
			///
			/// @return
			///
			virtual std::shared_ptr<base::IRandomAccessEnumerator<ItemType>> Clone() const override
			{
				return std::shared_ptr<RandomAccessEnumerator>{new RandomAccessEnumerator{*this}};
			}

			///
			/// @brief 容器中总共有多少个元素。
			///
			/// @return
			///
			virtual int64_t Count() const override
			{
				return _queue->Count();
			}

			///
			/// @brief 当前迭代到的位置。
			///
			/// @return
			///
			virtual int64_t Position() const override
			{
				return _index;
			}

			///
			/// @brief 将迭代器位置增加 value.
			///
			/// @param value 增加的值。可以是正数和负数。
			///
			virtual void Add(int64_t value) override
			{
				_index += value;
			}

			///
			/// @brief 获取当前值的引用。
			///
			/// @note 迭代器构造后，如果被迭代的集合不为空，要立即让 CurrentValue 指向第一个有效元素。
			///
			/// @return
			///
			virtual ItemType &CurrentValue() override
			{
				return _queue->Get(_index);
			}

			///
			/// @brief 派生类需要提供一个该对象。
			///
			/// @return
			///
			virtual base::IEnumerator<ItemType>::Context_t &Context() override
			{
				return _context;
			}

		}; // class Enumerator

		/* #endregion */

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

		/* #region GetRandomAccessEnumerator */

		using base::IRandomAccessEnumerable<ItemType>::GetRandomAccessEnumerator;

		///
		/// @brief 获取非 const 迭代器
		///
		/// @return
		///
		virtual std::shared_ptr<base::IRandomAccessEnumerator<ItemType>> GetRandomAccessEnumerator() override
		{
			return std::shared_ptr<RandomAccessEnumerator>{new RandomAccessEnumerator{*this}};
		}

		/* #endregion */
	};

} // namespace base

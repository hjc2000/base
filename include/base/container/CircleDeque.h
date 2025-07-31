#pragma once
#include "base/container/iterator/IEnumerable.h"
#include "base/container/iterator/IEnumerator.h"
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
	template <typename T, int64_t Size>
		requires(Size > 0)
	class CircleDeque final :
		public base::IDeque<T>,
		public base::IEnumerable<T>
	{
	private:
		/* #region Enumerator */

		class Enumerator final :
			public base::IEnumerator<T>
		{
		private:
			CircleDeque<T, Size> &_queue;
			int64_t _index = 0;

		public:
			Enumerator(CircleDeque<T, Size> &queue)
				: _queue(queue)
			{
			}

			///
			/// @brief 迭代器当前是否指向尾后元素。
			///
			/// @return
			///
			virtual bool IsEnd() const override
			{
				return _index >= _queue.Count();
			}

			///
			/// @brief 获取当前值的引用。
			///
			/// @return
			///
			virtual T &CurrentValue() override
			{
				return _queue[_index];
			}

			///
			/// @brief 递增迭代器的位置。
			///
			///
			virtual void Add() override
			{
				_index++;
			}

		}; // class Enumerator

		/* #endregion */

		alignas(T) uint8_t _memory_block[sizeof(T) * Size]{};
		base::Counter<uint64_t> _begin{0, Size - 1};
		base::Counter<uint64_t> _end{0, Size - 1};
		bool _is_full = false;

		T *Buffer()
		{
			return reinterpret_cast<T *>(_memory_block);
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

		///
		/// @brief 从队列末端入队。
		///
		/// @param obj
		///
		virtual void PushBack(T const &obj) override
		{
			if (_is_full)
			{
				throw std::runtime_error{CODE_POS_STR + "队列已满，无法入队。"};
			}

			new (&Buffer()[_end.CurrentValue()]) T{obj};
			_end++;
			if (_begin == _end)
			{
				_is_full = true;
			}
		}

		///
		/// @brief 从队列末端退队。
		///
		/// @return
		///
		virtual T PopBack() override
		{
			if (Count() == 0)
			{
				throw std::runtime_error{CODE_POS_STR + "队列为空，无法退队。"};
			}

			int64_t index = _end - 1;
			T ret{std::move(Buffer()[index])};
			Buffer()[index].~T();
			_end--;
			_is_full = false;
			return ret;
		}

		///
		/// @brief 尝试从队列末端退队。
		///
		/// @param out
		/// @return
		///
		virtual bool TryPopBack(T &out) override
		{
			if (Count() == 0)
			{
				return false;
			}

			int64_t index = _end - 1;
			out = std::move(Buffer()[index]);
			Buffer()[index].~T();
			_end--;
			_is_full = false;
			return true;
		}

		///
		/// @brief 从队列前端入队。
		///
		/// @param obj
		///
		virtual void PushFront(T const &obj) override
		{
			if (_is_full)
			{
				throw std::runtime_error{CODE_POS_STR + "队列已满，无法入队。"};
			}

			_begin--;
			new (&Buffer()[_begin.CurrentValue()]) T{obj};
			if (_begin == _end)
			{
				_is_full = true;
			}
		}

		///
		/// @brief 从队列前端退队。
		///
		/// @return
		///
		virtual T PopFront() override
		{
			if (Count() == 0)
			{
				throw std::runtime_error{CODE_POS_STR + "队列为空，无法退队。"};
			}

			int64_t index = _begin.CurrentValue();
			T ret{std::move(Buffer()[index])};
			Buffer()[index].~T();
			_begin++;
			_is_full = false;
			return ret;
		}

		///
		/// @brief 尝试从队列前端退队。
		///
		/// @param out
		/// @return
		///
		virtual bool TryPopFront(T &out) override
		{
			if (Count() == 0)
			{
				return false;
			}

			int64_t index = _begin.CurrentValue();
			out = std::move(Buffer()[index]);
			Buffer()[index].~T();
			_begin++;
			_is_full = false;
			return true;
		}

		///
		/// @brief 清空队列。
		///
		///
		virtual void Clear() override
		{
			for (int64_t i = 0; i < Count(); i++)
			{
				(*this)[i].~T();
			}

			_begin.Reset();
			_end.Reset();
			_is_full = false;
		}

		T &operator[](int64_t index)
		{
			if (index < 0 || index >= Count())
			{
				throw std::out_of_range{CODE_POS_STR + "索引越界。"};
			}

			int64_t real_index = _begin + index;
			return Buffer()[real_index];
		}

		T const &operator[](int64_t index) const
		{
			if (index < 0 || index >= Count())
			{
				throw std::out_of_range{CODE_POS_STR + "索引越界。"};
			}

			int64_t real_index = _begin + index;
			return Buffer()[real_index];
		}

		using base::IEnumerator<T>::GetEnumerator;

		///
		/// @brief 获取非 const 迭代器
		///
		/// @return
		///
		virtual std::shared_ptr<base::IEnumerator<T>> GetEnumerator() override
		{
			return std::shared_ptr<Enumerator>{new Enumerator{*this}};
		}
	};

} // namespace base

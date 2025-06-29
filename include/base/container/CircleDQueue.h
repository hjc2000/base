#pragma once
#include "base/math/Counter.h"
#include "base/string/define.h"
#include "IDQueue.h"
#include <algorithm>
#include <cstdint>
#include <stdexcept>

namespace base
{
	///
	/// @brief 循环缓冲区的双端队列。
	///
	///
	template <typename T, int32_t Size>
		requires(Size > 0)
	class CircleDQueue :
		base::IDQueue<T>
	{
	private:
		alignas(T) uint8_t _memory_block[sizeof(T) * Size]{};
		base::Counter<uint32_t> _begin{0, Size - 1};
		base::Counter<uint32_t> _end{0, Size - 1};
		bool _is_full = false;

		T *Buffer()
		{
			return reinterpret_cast<T *>(_memory_block);
		}

	public:
		///
		/// @brief 队列中当前元素的数量。
		///
		/// @return
		///
		virtual int32_t Count() const override
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

			int32_t index = _end - 1;
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

			int32_t index = _end - 1;
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

			int32_t index = _begin.CurrentValue();
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

			int32_t index = _begin.CurrentValue();
			out = std::move(Buffer()[index]);
			Buffer()[index].~T();
			_begin++;
			_is_full = false;
			return true;
		}
	};

} // namespace base

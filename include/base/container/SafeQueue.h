#pragma once
#include "base/container/IQueue.h"
#include "base/string/define.h"
#include "base/task/Mutex.h"
#include <cstdint>
#include <queue>
#include <stdexcept>

namespace base
{
	///
	/// @brief 线程安全的队列，加了互斥锁。
	/// @tparam T
	///
	template <typename T>
	class SafeQueue final :
		public base::IQueue<T>
	{
	private:
		std::queue<T> _queue;
		base::task::Mutex _lock{};

	public:
		/* #region 生命周期 */

		///
		/// @brief 构造一个空的队列。
		///
		SafeQueue() = default;

		///
		/// @brief 拷贝构造
		///
		/// @param o
		///
		SafeQueue(SafeQueue<T> const &o)
		{
			*this = o;
		}

		///
		/// @brief 移动构造
		///
		/// @param o
		///
		SafeQueue(SafeQueue<T> const &&o)
		{
			*this = o;
		}

		///
		/// @brief 拷贝赋值。
		///
		/// @param o
		/// @return base::SafeQueue<T>&
		///
		base::SafeQueue<T> &operator=(SafeQueue<T> const &o)
		{
			base::task::MutexGuard l[] = {_lock, o._lock};
			_queue = o._queue;
			return *this;
		}

		///
		/// @brief 移动赋值。
		///
		/// @param o
		/// @return base::SafeQueue<T>&
		///
		base::SafeQueue<T> &operator=(SafeQueue<T> const &&o)
		{
			base::task::MutexGuard l[] = {_lock, o._lock};
			_queue = std::move(o._queue);
			return *this;
		}

		/* #endregion */

		///
		/// @brief 队列中元素的数量。
		/// @return
		///
		virtual int64_t Count() const override
		{
			base::task::MutexGuard g{_lock};
			return _queue.size();
		}

		///
		/// @brief 退队。
		/// @return
		///
		virtual T Dequeue() override
		{
			base::task::MutexGuard g{_lock};
			if (_queue.empty())
			{
				throw std::underflow_error{CODE_POS_STR + "队列当前为空，无法退队"};
			}

			T ret = _queue.front();
			_queue.pop();
			return ret;
		}

		///
		/// @brief 尝试退队
		/// @param out 从队列里拿出来的元素会被赋值给 out，这要求 out 的类要实现赋值运算符。
		/// @return 退队成功返回 true，失败返回 false
		///
		virtual bool TryDequeue(T &out) override
		{
			base::task::MutexGuard g{_lock};
			if (_queue.empty())
			{
				return false;
			}

			out = _queue.front();
			_queue.pop();
			return true;
		}

		///
		/// @brief 入队
		/// @param obj
		///
		virtual void Enqueue(T const &obj) override
		{
			base::task::MutexGuard g{_lock};
			_queue.push(obj);
		}

		///
		/// @brief 清空队列。
		///
		virtual void Clear() override
		{
			base::task::MutexGuard g{_lock};
			_queue = std::queue<T>{};
		}
	};

} // namespace base

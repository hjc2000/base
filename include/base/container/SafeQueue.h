#pragma once
#ifndef HAS_THREAD
#define HAS_THREAD 0
#endif

#if HAS_THREAD
#include <atomic>
#include <base/container/IQueue.h>
#include <mutex>
#include <queue>
#include <stdexcept>

namespace base
{
	/// @brief 线程安全的队列，加了互斥锁。
	/// @tparam T
	template <typename T>
	class SafeQueue
		: public base::IQueue<T>
	{
	private:
		std::queue<T> _queue;
		std::mutex _lock;
		std::atomic<int32_t> _count = 0;

	public:
		/// @brief 队列中元素的数量。
		/// @return
		int32_t Count() const override
		{
			return _count;
		}

		/// @brief 退队。
		/// @return
		T Dequeue() override
		{
			std::lock_guard l(_lock);
			if (_queue.empty())
			{
				throw std::runtime_error("队列当前为空，无法退队");
			}

			T ret = _queue.front();
			_queue.pop();
			_count--;
			return ret;
		}

		/// @brief 尝试退队
		/// @param out 从队列里拿出来的元素会被赋值给 out，这要求 out 的类要实现赋值运算符。
		/// @return 退队成功返回 true，失败返回 false
		bool TryDequeue(T &out) override
		{
			std::lock_guard l(_lock);
			if (_queue.empty())
			{
				return false;
			}

			out = _queue.front();
			_queue.pop();
			_count--;
			return true;
		}

		/// @brief 入队
		/// @param obj
		void Enqueue(T obj) override
		{
			std::lock_guard l(_lock);
			_queue.push(obj);
			_count++;
		}

		/// @brief 清空队列。
		void Clear() override
		{
			std::lock_guard l(_lock);

			/*
			 * 构造一个空的队列，然后让 _queue 与空队列交换。退出作用域后，empty_queue
			 * 被销毁，所有元素都丢失。
			 *
			 * 这要求 T 类型必须不是在堆上创建的，否则会内存泄漏，因为本函数并不会 delete 每一个元素。
			 */
			std::queue<T> empty_queue;
			_queue.swap(empty_queue);
			_count = 0;
		}
	};
}
#endif // HAS_THREAD
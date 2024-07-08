#pragma once
#include <base/container/IQueue.h>
#include <queue>
#include <stdexcept>

namespace base
{
	/// @brief 队列
	/// @note 本队列装的类必须实现拷贝构造函数和赋值运算符。
	/// @note 禁止使用 new 创建出对象后将对象的指针装入本队列，当退队或清空队列时会造成内存泄漏。
	///
	/// @tparam T
	template <typename T>
	class Queue : public IQueue<T>
	{
	private:
		std::queue<T> _queue;

	public:
		/// @brief 当前队列中元素的数量。
		/// @return
		uint64_t Count() const override
		{
			return _queue.size();
		}

		/// @brief 退队
		/// @return
		/// @exception 如果队列为空，会抛出 underflow_error
		T Dequeue() override
		{
			if (_queue.empty())
			{
				throw std::underflow_error("队列当前为空，无法退队");
			}

			T ret = _queue.front();
			_queue.pop();
			return ret;
		}

		/// @brief 尝试退队
		/// @param out 从队列里拿出来的元素会被赋值给 out，这要求 out 的类要实现赋值运算符。
		/// @return 退队成功返回 true，失败返回 false
		bool TryDequeue(T &out) override
		{
			if (_queue.empty())
			{
				return false;
			}

			out = _queue.front();
			_queue.pop();
			return true;
		}

		/// @brief 入队
		/// @param obj
		void Enqueue(T obj) override
		{
			_queue.push(obj);
		}

		/// @brief 清空队列。
		void Clear() override
		{
			/* 构造一个空的队列，然后让 _queue 与空队列交换。退出作用域后，empty_queue
			 * 被销毁，所有元素都丢失。
			 *
			 * 这要求 T 类型必须不是在堆上创建的，否则会内存泄漏，因为本函数并不会 delete 每一个元素。
			 */
			std::queue<T> empty_queue;
			_queue.swap(empty_queue);
		}
	};
}

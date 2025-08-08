#pragma once
#include "base/container/IQueue.h"
#include "base/string/define.h"
#include <cstdint>
#include <deque>
#include <stdexcept>

namespace base
{
	///
	/// @brief 队列
	///
	/// @note 本队列装的类必须实现拷贝构造函数和赋值运算符。
	/// @note 禁止使用 new 创建出对象后将对象的指针装入本队列，当退队或清空队列时会造成内存泄漏。
	///
	/// @tparam T
	///
	template <typename T>
	class Queue final :
		public IQueue<T>
	{
	private:
		std::deque<T> _queue{};

	public:
		///
		/// @brief 构造一个空的队列。
		///
		Queue() = default;

		///
		/// @brief 当前队列中元素的数量。
		///
		/// @return
		///
		virtual int64_t Count() const override
		{
			return _queue.size();
		}

		///
		/// @brief 退队
		///
		/// @return
		///
		/// @exception 如果队列为空，会抛出 underflow_error
		///
		virtual T Dequeue() override
		{
			if (_queue.empty())
			{
				throw std::underflow_error{CODE_POS_STR + "队列当前为空，无法退队"};
			}

			T ret = _queue.front();
			_queue.pop_front();
			return ret;
		}

		///
		/// @brief 尝试退队
		///
		/// @param out 从队列里拿出来的元素会被赋值给 out，这要求 out 的类要实现赋值运算符。
		///
		/// @return 退队成功返回 true，失败返回 false
		///
		virtual bool TryDequeue(T &out) override
		{
			if (_queue.empty())
			{
				return false;
			}

			out = _queue.front();
			_queue.pop_front();
			return true;
		}

		///
		/// @brief 入队
		///
		/// @param obj
		///
		virtual void Enqueue(T const &obj) override
		{
			_queue.push_back(obj);
		}

		///
		/// @brief 清空队列。
		///
		virtual void Clear() override
		{
			_queue.clear();
		}

		T &operator[](int64_t index)
		{
			return _queue[index];
		}

		T const &operator[](int64_t index) const
		{
			return _queue[index];
		}

		T &Get(int64_t index)
		{
			return _queue[index];
		}

		T const &Get(int64_t index) const
		{
			return _queue[index];
		}

		void Set(int64_t index, T const &value)
		{
			_queue[index] = value;
		}

		/* #region 迭代 */

		auto begin()
		{
			return _queue.begin();
		}

		auto end()
		{
			return _queue.end();
		}

		auto begin() const
		{
			return _queue.begin();
		}

		auto end() const
		{
			return _queue.end();
		}

		/* #endregion */
	};

} // namespace base

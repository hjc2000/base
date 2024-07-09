#pragma once
#ifndef HAS_THREAD
#define HAS_THREAD 0
#endif

#include <atomic>
#include <base/IDisposable.h>
#include <base/container/Queue.h>

#if HAS_THREAD
#include <condition_variable>
#include <iostream>
#include <mutex>
#endif

namespace base
{
	/// @brief 数据缓存。
	/// @note 可以往里放入数据和取出数据。本质上是一个队列。
	/// 当队列的元素数量超过上限时会丢弃最开始的数据。
	///
	/// @tparam T
	template <typename T>
	class DataChach
		: public IDisposable
	{
	private:
		int _max_count;
		Queue<T> _queue;

#if HAS_THREAD
		std::atomic_bool _disposed = false;
		std::mutex _lock;
		std::condition_variable _can_tack_out;
#endif

	public:
		/// <summary>
		///
		/// </summary>
		/// <param name="max_count">必须大于等于 1，否则会抛出异常。</param>
		DataChach(int max_count)
		{
			if (max_count < 1)
			{
				throw std::invalid_argument{"max_count 必须大于等于 1"};
			}

			_max_count = max_count;
		}

		~DataChach()
		{
			Dispose();
		}

		void Dispose() override
		{
			if (_disposed)
			{
				return;
			}

			_disposed = true;
		}

		/// <summary>
		///		将数据放到内部队列的末尾。
		/// </summary>
		void PushBack(T item)
		{
#if HAS_THREAD
			std::lock_guard l{_lock};
#endif

			_queue.Enqueue(item);
			if (_queue.Count() > _max_count)
			{
				std::cout << "警告，数据队列元素超过最大值，丢弃最开始的数据。" << std::endl;
				_queue.Dequeue();
			}
		}

		/// <summary>
		///		取出数据。如果当前无数据可取会阻塞，直到有数据。取出后，数据将从内部队列中删除。
		/// </summary>
		/// <returns></returns>
		T TackOut()
		{
#if HAS_THREAD
			std::unique_lock l{_lock};

			auto p = [&]()
			{
				if (_disposed)
				{
					return true;
				}

				return _queue.Count() > 0;
			};
			_can_tack_out.wait(l, p);
#endif

			if (_disposed)
			{
				throw std::runtime_error{"已经释放了"};
			}

			return _queue.Dequeue();
		}
	};
}
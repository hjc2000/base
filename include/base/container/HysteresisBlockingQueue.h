#pragma once
#include "base/container/SafeQueue.h"
#include "base/IDisposable.h"
#include "base/task/IMutex.h"
#include "base/task/Semaphore.h"
#include <atomic>

namespace base
{
	///
	/// @brief 带有滞回特性的阻塞队列。
	///
	/// 	@note 队列满时，再往里送会阻塞，直到队列中的元素被消费到小于一定阈值才取消阻塞。
	///
	/// 	@note 队列空时，再往外拿会阻塞，直到队列中的元素大于一定阈值才取消阻塞。
	///
	/// 	@note 本队列线程安全。
	///
	/// @tparam T
	///
	template <typename T>
	class HysteresisBlockingQueue final :
		public base::IQueue<T>,
		public base::IDisposable
	{
	private:
		std::atomic_bool _disposed = false;

		///
		/// @brief 为 true 表示被冲洗了。
		/// @note 被冲洗后入队会抛出异常。
		/// @note 被冲洗后出队不会再被阻塞。
		///
		std::atomic_bool _flushed = false;

		///
		/// @brief 队列容量的上限。
		///
		int32_t _max = 0;

		///
		/// @brief 队列元素数量小于此值时取消对入队的阻塞。
		///
		int32_t _threshold = 0;

		base::SafeQueue<T> _queue;

		std::shared_ptr<base::IMutex> _lock = base::CreateIMutex();

		///
		/// @brief 队列被消费了，需要入队了，就触发此信号。
		/// @note 因为依赖 _max ，所以在构造函数中初始化。
		///
		base::Semaphore _queue_consumed_signal;

		///
		/// @brief 队列中有数据，可以退队时触发此信号。
		/// @note 初始时队列为空，无法退队，所以初始计数为 0.
		///
		base::Semaphore _queue_avaliable_signal{0};

	public:
		///
		/// @brief 构造函数
		/// @param max 队列能容纳的元素的最大数量。
		///
		HysteresisBlockingQueue(int32_t max)
			: _queue_consumed_signal(max) // 初始时队列为空，允许入队 _max 次，所以初始计数为 _max.
		{
			if (max <= 0)
			{
				throw std::invalid_argument{"最大值不能 <= 0"};
			}

			_max = max;
			_threshold = _max / 2;
		}

		~HysteresisBlockingQueue()
		{
			Dispose();
		}

		///
		/// @brief 释放
		///
		/// @note 会清空队列。
		/// @note 会取消所有阻塞，并且不再具有阻塞能力。
		///
		void Dispose() override
		{
			if (_disposed)
			{
				return;
			}

			_disposed = true;

			_queue.Clear();
			_queue_consumed_signal.Dispose();
			_queue_avaliable_signal.Dispose();
		}

		///
		/// @brief 队列中当前元素个数
		/// @return
		///
		int32_t Count() const override
		{
			// _queue 线程安全，这里不需要加锁。
			return _queue.Count();
		}

		///
		/// @brief 退队。
		/// @note 队列空了再次尝试退队会受到阻塞，直到队列里的元素数量大于阈值。
		/// @note 在 Dispose 或 Flush 或析构函数执行后，本方法会被无条件取消阻塞，此时如果队列为空，
		/// 会抛出异常。
		///
		/// @return 退队的元素。
		///
		T Dequeue() override
		{
			while (true)
			{
				if (_disposed)
				{
					throw std::runtime_error{"队列已被释放，无法退队。"};
				}

				// 在持有互斥锁的条件下检查，避免误触，以及操作
				{
					base::LockGuard g{*_lock};
					if (_queue.Count() > 0)
					{
						T element = _queue.Dequeue();
						if (_queue.Count() <= _threshold)
						{
							_queue_consumed_signal.Release(_max - _queue.Count());
						}

						return element;
					}

					if (_flushed && _queue.Count() == 0)
					{
						// 冲洗后，要强行退队，即使队列为空，这是为了引发异常。
						T element = _queue.Dequeue();
						return element;
					}
				}

				if (!_flushed)
				{
					_queue_avaliable_signal.Acquire();
				}
			}
		}

		///
		/// @brief 尝试退队
		/// @param out
		/// @return 退队成功返回 true，失败返回 false。
		///
		bool TryDequeue(T &out) override
		{
			while (true)
			{
				if (_disposed)
				{
					throw std::runtime_error{"队列已被释放，无法退队。"};
				}

				// 在持有互斥锁的条件下检查，避免误触，以及操作
				{
					base::LockGuard g{*_lock};
					if (_queue.Count() > 0)
					{
						bool result = _queue.TryDequeue(out);
						if (_queue.Count() <= _threshold)
						{
							_queue_consumed_signal.Release(_max - _queue.Count());
						}

						return result;
					}

					if (_flushed && _queue.Count() == 0)
					{
						// 冲洗后，要强行退队，即使队列为空，这是为了引发异常。
						T element = _queue.Dequeue();
						return element;
					}
				}

				if (!_flushed)
				{
					_queue_avaliable_signal.Acquire();
				}
			}
		}

		///
		/// @brief 入队。
		/// @note 如果队列满了会受到阻塞，直到队列元素被消费到小于阈值时才取消阻塞。
		/// @note Dispose 和 Flush 会无条件取消阻塞。但是，Dispose 和 Flush 后，
		/// 再次尝试入队会抛出异常。
		///
		/// @param obj
		///
		void Enqueue(T const &obj) override
		{
			while (true)
			{
				if (_disposed)
				{
					throw std::runtime_error{"队列已被释放，无法入队。"};
				}

				if (_flushed)
				{
					throw std::runtime_error{"队列已被冲洗，无法入队。"};
				}

				// 在持有互斥锁的条件下检查，避免误触，以及操作
				{
					base::LockGuard g{*_lock};
					if (_queue.Count() < _max)
					{
						_queue.Enqueue(obj);
						if (_queue.Count() >= _threshold)
						{
							_queue_avaliable_signal.Release(_queue.Count());
						}

						return;
					}
				}

				_queue_consumed_signal.Acquire();
			}
		}

		///
		/// @brief 清空队列
		///
		void Clear() override
		{
			if (_disposed)
			{
				throw std::runtime_error{"此对象已释放，不能再使用"};
			}

			_queue.Clear();
			_queue_consumed_signal.Release(_max);
		}

		///
		/// @brief 冲洗队列。
		/// @note 冲洗后，再尝试入队会抛出异常。
		/// @note 冲洗后，出队操作将不会被阻塞，即使队列中为空。
		///
		void Flush()
		{
			if (_disposed)
			{
				throw std::runtime_error{"此对象已释放，不能再使用"};
			}

			_flushed = true;
			_queue_avaliable_signal.Dispose();
			_queue_consumed_signal.Dispose();
		}

		///
		/// @brief 检查队列是否已被冲洗。
		/// @return
		///
		bool Flushed()
		{
			return _flushed;
		}
	};
} // namespace base

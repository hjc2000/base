#pragma once
#include "base/container/SafeQueue.h"
#include "base/IDisposable.h"
#include "base/string/define.h"
#include "base/task/Mutex.h"
#include "base/task/Semaphore.h"
#include <atomic>
#include <cstdint>
#include <exception>
#include <stdexcept>

namespace base
{
	///
	/// @brief 阻塞队列。
	///
	/// @tparam T
	///
	template <typename T>
	class BlockingQueue final :
		public base::IQueue<T>,
		public base::IDisposable
	{
	private:
		std::atomic_bool _disposed = false;

		///
		/// @brief 队列容量的上限。
		///
		int64_t _max = 0;

		base::SafeQueue<T> _queue;

		base::task::Mutex _lock{};

		///
		/// @brief 队列被消费了，需要入队了，就触发此信号。
		///
		/// @note 因为依赖 _max ，所以在构造函数中初始化。
		///
		base::Semaphore _queue_consumed_signal;

		///
		/// @brief 队列中有数据，可以退队时触发此信号。
		///
		/// @note 初始时队列为空，无法退队，所以初始计数为 0.
		///
		base::Semaphore _queue_avaliable_signal{0};

	public:
		///
		/// @brief 构造函数
		///
		/// @param max 队列能容纳的元素的最大数量。
		///
		BlockingQueue(int64_t max)
			: // 初始时队列为空，允许入队 _max 次，所以初始计数为 _max.
			  _queue_consumed_signal(max)
		{
			if (max <= 0)
			{
				throw std::invalid_argument{"最大值不能 <= 0"};
			}

			_max = max;
		}

		~BlockingQueue()
		{
			Dispose();
		}

		///
		/// @brief 释放
		///
		/// @note 会取消所有阻塞，并且不再具有阻塞能力。
		///
		/// @note 释放后入队会直接引发异常。
		///
		/// @note 释放后可以继续退队，取出残留的数据，直到队列为空，此时继续退队会触发退队失败，
		/// 和正常队列的效果一样。
		///
		virtual void Dispose() override
		{
			if (_disposed)
			{
				return;
			}

			_disposed = true;

			_queue_consumed_signal.Dispose();
			_queue_avaliable_signal.Dispose();
		}

		///
		/// @brief 队列是否已经被释放。
		///
		/// @return
		///
		bool Disposed() const
		{
			return _disposed;
		}

		///
		/// @brief 队列中当前元素个数
		///
		/// @return
		///
		virtual int64_t Count() const override
		{
			return _queue.Count();
		}

		///
		/// @brief 退队。
		///
		/// @return 退队的元素。
		///
		/// @exception underflow_error 本对象被处置后，本方法会无条件取消阻塞，并且不再具有阻塞能力，
		/// 此时如果队列为空，会抛出异常。
		///
		virtual T Dequeue() override
		{
			while (true)
			{
				// 在持有互斥锁的条件下检查，避免误触，以及操作
				{
					base::task::MutexGuard g{_lock};
					if (_disposed || _queue.Count() > 0)
					{
						T element = _queue.Dequeue();
						_queue_consumed_signal.ReleaseAll();
						return element;
					}
				}

				try
				{
					_queue_avaliable_signal.Acquire();
				}
				catch (base::ObjectDisposedException const &e)
				{
					// 不处理，继续下一轮循环。
				}
				catch (std::exception const &e)
				{
					throw std::runtime_error{CODE_POS_STR + e.what()};
				}
				catch (...)
				{
					throw std::runtime_error{CODE_POS_STR + "未知异常。"};
				}
			}
		}

		///
		/// @brief 尝试退队
		///
		virtual void TryDequeue(base::Placement<T> &placement) override
		{
			// 在持有互斥锁的条件下检查，避免误触，以及操作
			base::task::MutexGuard g{_lock};
			_queue.TryDequeue(placement);
			if (placement.Available())
			{
				_queue_consumed_signal.ReleaseAll();
			}
		}

		///
		/// @brief 入队。
		///
		/// @param obj
		///
		/// @exception ObjectDisposedException 本对象被处置后，继续入队会引发异常。
		///
		virtual void Enqueue(T const &obj) override
		{
			while (true)
			{
				if (_disposed)
				{
					throw base::ObjectDisposedException{CODE_POS_STR + "队列已被释放，无法入队。"};
				}

				// 在持有互斥锁的条件下检查，避免误触，以及操作
				{
					base::task::MutexGuard g{_lock};
					if (_queue.Count() < _max)
					{
						_queue.Enqueue(obj);
						_queue_avaliable_signal.ReleaseAll();
						return;
					}
				}

				try
				{
					_queue_consumed_signal.Acquire();
				}
				catch (base::ObjectDisposedException const &e)
				{
					// 不处理，继续下一轮循环。
				}
				catch (std::exception const &e)
				{
					throw std::runtime_error{CODE_POS_STR + e.what()};
				}
				catch (...)
				{
					throw std::runtime_error{CODE_POS_STR + "未知的异常。"};
				}
			}
		}

		///
		/// @brief 清空队列
		///
		virtual void Clear() override
		{
			_queue.Clear();
			_queue_consumed_signal.ReleaseAll();
		}
	};

} // namespace base

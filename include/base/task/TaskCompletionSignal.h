#pragma once
#include "base/define.h"
#include "base/IDisposable.h"
#include "base/string/define.h"
#include "ITask.h"
#include "Mutex.h"
#include "Semaphore.h"
#include <atomic>
#include <memory>

namespace base::task
{
	///
	/// @brief 任务完成信号。
	///
	///
	class TaskCompletionSignal final :
		public base::task::ITask
	{
	private:
		DELETE_COPY_AND_MOVE(TaskCompletionSignal)

		///
		/// @brief 共享指针本身不是线程安全的，多线程同时读写需要加锁。
		///
		///
		base::task::Mutex _lock{};

		///
		/// @brief 共享指针本身不是线程安全的，多线程同时读写需要加锁。
		///
		///
		std::shared_ptr<base::Semaphore> _semaphore = nullptr;

		std::atomic_bool _disposed = false;

	public:
		///
		/// @brief 构造函数。
		///
		/// @param completed 任务初始时是否处于已完成状态。
		///
		TaskCompletionSignal(bool completed)
		{
			if (!completed)
			{
				// 任务初始时是未完成状态
				Reset();
			}
		}

		///
		/// @brief 析构函数。析构时会调用 Dispose 方法。
		///
		///
		~TaskCompletionSignal()
		{
			Dispose();
		}

		///
		/// @brief 释放后，本对象将不再具有阻塞的能力，正在阻塞的 Wait 会立刻停止阻塞。
		///
		void Dispose()
		{
			if (_disposed)
			{
				return;
			}

			_disposed = true;

			// 让正在阻塞的 Wait 立刻停止阻塞。
			SetResult();
		}

		///
		/// @brief 如果 Dispose 被调用，本方法将永远返回 true，此时任务被锁定在完成状态，Reset
		/// 方法不再具有效果。这种情况下，本对象的 Wait 将不再具有阻塞的能力。
		///
		/// @return
		///
		virtual bool IsCompleted() const override
		{
			base::task::MutexGuard g{_lock};
			if (_disposed)
			{
				return true;
			}

			if (_semaphore == nullptr)
			{
				return true;
			}

			return false;
		}

		///
		/// @brief 等待，直到完成信号被触发。
		///
		virtual void Wait() override
		{
			// 如果调用了 Reset 方法，里面会调用信号量的 Dispose 方法，
			// 但是没关系，这里是循环，下一个循环还会继续等待。这样就不会因为调用 Reset
			// 方法导致放过一些早早开始等待的线程了。
			while (true)
			{
				if (_disposed)
				{
					throw base::ObjectDisposedException{CODE_POS_STR + "已经释放，无法等待。"};
				}

				std::shared_ptr<base::Semaphore> signal = nullptr;

				{
					base::task::MutexGuard g{_lock};

					// 在持有互斥锁的情况下捕获。
					//
					// 智能指针本身不是原子的，如果另一个线程正在编辑 _semaphore 字段，
					// 这里不持有互斥锁，直接同时拷贝，会发生竞态。
					signal = _semaphore;
				}

				if (signal == nullptr)
				{
					return;
				}

				try
				{
					signal->Acquire();
				}
				catch (...)
				{
				}
			}
		}

		///
		/// @brief 触发完成信号。
		///
		void SetResult()
		{
			base::task::MutexGuard g{_lock};
			if (_disposed)
			{
				return;
			}

			if (_semaphore == nullptr)
			{
				// 这里是读取智能指针，表面上看好像不用加锁，但是实际上智能指针本身不是原子的，
				// 一个线程写的同时另一个线程读不安全。所以这里在持有互斥锁的情况下操作。
				return;
			}

			_semaphore->Dispose();
			_semaphore = nullptr;
		}

		///
		/// @brief 重置完成状态。重置完了之后下一次 Wait 将会被阻塞。
		///
		void Reset()
		{
			base::task::MutexGuard g{_lock};
			if (_semaphore != nullptr)
			{
				_semaphore->Dispose();
				_semaphore = nullptr;
			}

			_semaphore = std::shared_ptr<base::Semaphore>{new base::Semaphore{0}};
		}
	};

	class TaskCompletionSignalGuard
	{
	private:
		base::task::TaskCompletionSignal &_signal;

	public:
		TaskCompletionSignalGuard(base::task::TaskCompletionSignal &signal)
			: _signal(signal)
		{
		}

		~TaskCompletionSignalGuard()
		{
			_signal.SetResult();
		}
	};

} // namespace base::task

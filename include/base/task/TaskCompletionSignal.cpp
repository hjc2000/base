#include "TaskCompletionSignal.h"
#include "base/IDisposable.h"
#include "base/string/define.h"
#include "Mutex.h"
#include "Semaphore.h"
#include <memory>

base::task::TaskCompletionSignal::TaskCompletionSignal(bool completed)
{
	if (!completed)
	{
		// 任务初始时是未完成状态
		Reset();
	}
}

base::task::TaskCompletionSignal::~TaskCompletionSignal()
{
	Dispose();
}

void base::task::TaskCompletionSignal::Dispose()
{
	if (_disposed)
	{
		return;
	}

	_disposed = true;

	// 让正在阻塞的 Wait 立刻停止阻塞。
	SetResult();
}

bool base::task::TaskCompletionSignal::IsCompleted() const
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

void base::task::TaskCompletionSignal::Wait()
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

void base::task::TaskCompletionSignal::SetResult()
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

void base::task::TaskCompletionSignal::Reset()
{
	base::task::MutexGuard g{_lock};
	if (_semaphore != nullptr)
	{
		_semaphore->Dispose();
		_semaphore = nullptr;
	}

	_semaphore = std::shared_ptr<base::Semaphore>{new base::Semaphore{0}};
}

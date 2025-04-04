#include "TaskCompletionSignal.h"
#include "base/IDisposable.h"
#include "base/string/define.h"
#include "Semaphore.h"
#include <memory>

base::TaskCompletionSignal::TaskCompletionSignal(bool completed)
{
	if (!completed)
	{
		// 任务初始时是未完成状态
		Reset();
	}
}

base::TaskCompletionSignal::~TaskCompletionSignal()
{
	Dispose();
}

void base::TaskCompletionSignal::Dispose()
{
	if (_disposed)
	{
		return;
	}

	_disposed = true;

	// 让正在阻塞的 Wait 立刻停止阻塞。
	SetResult();
}

bool base::TaskCompletionSignal::IsCompleted() const
{
	base::LockGuard g{*_lock};
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

void base::TaskCompletionSignal::Wait()
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
			base::LockGuard g{*_lock};

			// 在持有互斥锁的情况下捕获
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

void base::TaskCompletionSignal::SetResult()
{
	base::LockGuard g{*_lock};
	if (_semaphore != nullptr)
	{
		_semaphore->Dispose();
		_semaphore = nullptr;
	}
}

void base::TaskCompletionSignal::Reset()
{
	base::LockGuard g{*_lock};
	if (_semaphore != nullptr)
	{
		_semaphore->Dispose();
		_semaphore = nullptr;
	}

	_semaphore = std::shared_ptr<base::Semaphore>{new base::Semaphore{0}};
}

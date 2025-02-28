#include "TaskCompletionSignal.h"
#include <base/string/define.h>

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

bool base::TaskCompletionSignal::IsCompleted()
{
	base::LockGuard g{*_lock};
	if (_disposed)
	{
		return true;
	}

	if (_task_completion_signal == nullptr)
	{
		return true;
	}

	return false;
}

void base::TaskCompletionSignal::Wait()
{
	/**
	 * 这里的设计目标是本类对象被 Dispose 后，已经进入等待的线程不会引发异常，新的要进入
	 * 等待的会引发异常。
	 *
	 * 所以在循环内检查到 _disposed 为 true 不会抛出异常。进入循环前则会。
	 */
	if (_disposed)
	{
		throw std::runtime_error{CODE_POS_STR + "已经释放，无法等待。"};
	}

	while (true)
	{
		std::shared_ptr<base::ISemaphore> signal = nullptr;

		{
			base::LockGuard g{*_lock};
			if (_disposed)
			{
				return;
			}

			if (_task_completion_signal == nullptr)
			{
				return;
			}

			// 在持有互斥锁的情况下捕获
			signal = _task_completion_signal;
		}

		if (signal != nullptr)
		{
			try
			{
				signal->Acquire();
			}
			catch (...)
			{
				// 信号量被 Dispose 后就会抛出异常。
			}

			return;
		}
	}
}

void base::TaskCompletionSignal::SetResult()
{
	base::LockGuard g{*_lock};
	if (_task_completion_signal != nullptr)
	{
		_task_completion_signal->Dispose();
		_task_completion_signal = nullptr;
	}
}

void base::TaskCompletionSignal::Reset()
{
	base::LockGuard g{*_lock};
	if (_task_completion_signal != nullptr)
	{
		_task_completion_signal->Dispose();
		_task_completion_signal = nullptr;
	}

	_task_completion_signal = base::di::CreateISemaphore(0);
}

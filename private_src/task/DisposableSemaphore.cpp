#include "DisposableSemaphore.h"

#if HAS_THREAD

base::DisposableSemaphore::DisposableSemaphore(int initial_count)
	: _semaphore(initial_count)
{
}

void base::DisposableSemaphore::Dispose()
{
	if (_disposed)
	{
		return;
	}

	_disposed = true;

	// 只要并发数不超过 INT32_MAX，配合 _disposed，这会让信号量不再具备阻塞能力。
	_semaphore.release(INT32_MAX);
}

void base::DisposableSemaphore::Release(int count)
{
	_semaphore.release(count);
}

void base::DisposableSemaphore::Acquire()
{
	if (_disposed)
	{
		throw std::runtime_error{"信号量已经释放，无法获取。"};
	}

	_semaphore.acquire();
	if (_disposed)
	{
		throw std::runtime_error{"信号量已经释放，无法获取。"};
	}
}

bool base::DisposableSemaphore::TryAcquire(base::Seconds const &timeout)
{
	if (_disposed)
	{
		throw std::runtime_error{"信号量已经释放，无法获取。"};
	}

	bool result = _semaphore.try_acquire_for(static_cast<std::chrono::milliseconds>(timeout));
	if (_disposed)
	{
		throw std::runtime_error{"信号量已经释放，无法获取。"};
	}

	return result;
}

#endif // HAS_THREAD

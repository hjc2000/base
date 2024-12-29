#include "DisposableSemaphore.h"
#include <base/string/define.h>

#if HAS_THREAD

base::DisposableSemaphore::DisposableSemaphore(int32_t initial_count)
	: _semaphore(initial_count)
{
}

base::DisposableSemaphore::~DisposableSemaphore()
{
	Dispose();
}

void base::DisposableSemaphore::Dispose()
{
	if (_disposed)
	{
		return;
	}

	_disposed = true;
	_semaphore.release(INT32_MAX);
}

void base::DisposableSemaphore::Release(int32_t count)
{
	_semaphore.release(count);
}

void base::DisposableSemaphore::Acquire()
{
	if (_disposed)
	{
		throw std::runtime_error{CODE_POS_STR + "信号量已经释放，无法获取。"};
	}

	_semaphore.acquire();
	if (_disposed)
	{
		throw std::runtime_error{CODE_POS_STR + "信号量已经释放，无法获取。"};
	}
}

bool base::DisposableSemaphore::TryAcquire(base::Seconds const &timeout)
{
	if (_disposed)
	{
		throw std::runtime_error{CODE_POS_STR + "信号量已经释放，无法获取。"};
	}

	bool result = _semaphore.try_acquire_for(static_cast<std::chrono::milliseconds>(timeout));
	if (_disposed)
	{
		throw std::runtime_error{CODE_POS_STR + "信号量已经释放，无法获取。"};
	}

	return result;
}

#endif // HAS_THREAD

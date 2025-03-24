#include "DisposableSemaphore.h"
#include <cstdint>

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
	Release(INT32_MAX);
}

void base::DisposableSemaphore::Release(int32_t count)
{
	if (count <= 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "count 不能 <= 0."};
	}

	_semaphore.release(count);
}

void base::DisposableSemaphore::ReleaseFromISR(int32_t count)
{
	Release(count);
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
	if (timeout < 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "超时时间不能 <=0."};
	}

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

#include "DisposableSemaphore.h"

#if HAS_THREAD
	#include <base/string/define.h>

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

	ReleaseAllAcquire();
}

void base::DisposableSemaphore::Release(int32_t count)
{
	if (count <= 0)
	{
		throw std::invalid_argument{CODE_POS_STR + "count 不能 <=0."};
	}

	std::lock_guard g{_lock};
	_semaphore.release(count);
}

void base::DisposableSemaphore::ReleaseAllAcquire()
{
	std::lock_guard g{_lock};
	if (_acquirer_count > 0)
	{
		_semaphore.release(_acquirer_count);
	}
}

void base::DisposableSemaphore::Acquire()
{
	{
		std::lock_guard g{_lock};
		if (_disposed)
		{
			throw std::runtime_error{CODE_POS_STR + "信号量已经释放，无法获取。"};
		}

		_acquirer_count++;
	}

	_semaphore.acquire();

	{
		std::lock_guard g{_lock};
		if (_disposed)
		{
			throw std::runtime_error{CODE_POS_STR + "信号量已经释放，无法获取。"};
		}

		_acquirer_count--;
	}
}

bool base::DisposableSemaphore::TryAcquire(base::Seconds const &timeout)
{
	{
		std::lock_guard g{_lock};
		if (_disposed)
		{
			throw std::runtime_error{CODE_POS_STR + "信号量已经释放，无法获取。"};
		}

		_acquirer_count++;
	}

	bool result = _semaphore.try_acquire_for(static_cast<std::chrono::milliseconds>(timeout));

	{
		std::lock_guard g{_lock};
		if (_disposed)
		{
			throw std::runtime_error{CODE_POS_STR + "信号量已经释放，无法获取。"};
		}

		_acquirer_count--;
	}

	return result;
}

#endif // HAS_THREAD

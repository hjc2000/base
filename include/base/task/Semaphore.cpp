#include "Semaphore.h"
#include "base/string/define.h"
#include "IBaseSemaphore.h"
#include "Mutex.h"

base::Semaphore::Semaphore(int32_t initial_count)
{
	_base_semaphore = base::CreateBaseSemaphore(initial_count);
}

void base::Semaphore::Dispose()
{
	if (_disposed)
	{
		return;
	}

	_disposed = true;
	ReleaseAll();
}

void base::Semaphore::Release(int32_t count)
{
	_base_semaphore->Release(count);
}

void base::Semaphore::ReleaseAll()
{
	base::task::MutexGuard g{_lock};
	if (_acquire_count > 0)
	{
		_base_semaphore->Release(_acquire_count);
	}
}

void base::Semaphore::ReleaseFromISR(int32_t count)
{
	_base_semaphore->ReleaseFromISR(count);
}

void base::Semaphore::ReleaseAllFromISR()
{
	base::task::MutexGuard g{_lock};
	if (_acquire_count > 0)
	{
		_base_semaphore->ReleaseFromISR(_acquire_count);
	}
}

void base::Semaphore::Acquire()
{
	{
		base::task::MutexGuard g{_lock};
		if (_disposed)
		{
			throw base::ObjectDisposedException{CODE_POS_STR + "已经释放，无法获取。"};
		}

		_acquire_count++;
	}

	_base_semaphore->Acquire();

	{
		base::task::MutexGuard g{_lock};
		_acquire_count--;
		if (_disposed)
		{
			throw base::ObjectDisposedException{CODE_POS_STR + "已经释放，无法获取。"};
		}
	}
}

bool base::Semaphore::TryAcquire(base::Seconds const &timeout)
{
	{
		base::task::MutexGuard g{_lock};
		if (_disposed)
		{
			throw base::ObjectDisposedException{CODE_POS_STR + "已经释放，无法获取。"};
		}

		_acquire_count++;
	}

	bool result = _base_semaphore->TryAcquire(timeout);

	{
		base::task::MutexGuard g{_lock};
		_acquire_count--;
		if (_disposed)
		{
			throw base::ObjectDisposedException{CODE_POS_STR + "已经释放，无法获取。"};
		}
	}

	return result;
}

void base::Semaphore::Release()
{
	Release(1);
}

void base::Semaphore::ReleaseFromISR()
{
	ReleaseFromISR(1);
}

#include "Semaphore.h"
#include "base/LockGuard.h"
#include "base/string/define.h"
#include "IBaseSemaphore.h"
#include <stdexcept>

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
	base::LockGuard l{*_lock};
	_base_semaphore->Release(_acquire_count);
}

void base::Semaphore::ReleaseFromISR(int32_t count)
{
	_base_semaphore->ReleaseFromISR(count);
}

void base::Semaphore::ReleaseAllFromISR()
{
	base::LockGuard l{*_lock};
	_base_semaphore->ReleaseFromISR(_acquire_count);
}

void base::Semaphore::Acquire()
{
	{
		base::LockGuard l{*_lock};
		if (_disposed)
		{
			throw std::runtime_error{CODE_POS_STR + "已经释放，无法获取。"};
		}

		_acquire_count++;
	}

	_base_semaphore->Acquire();

	{
		base::LockGuard l{*_lock};
		_acquire_count--;
		if (_disposed)
		{
			throw std::runtime_error{CODE_POS_STR + "已经释放，无法获取。"};
		}
	}
}

bool base::Semaphore::TryAcquire(base::Seconds const &timeout)
{
	{
		base::LockGuard l{*_lock};
		if (_disposed)
		{
			return false;
		}

		_acquire_count++;
	}

	bool result = _base_semaphore->TryAcquire(timeout);

	{
		base::LockGuard l{*_lock};
		_acquire_count--;
		if (_disposed)
		{
			return false;
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

#include "BinarySemaphore.h"
#include "base/unit/Nanoseconds.h"
#include <chrono>

#if HAS_THREAD

base::BinarySemaphore::BinarySemaphore(bool initial_release)
	: _bs(initial_release)
{
}

void base::BinarySemaphore::Release()
{
	_bs.release();
}

void base::BinarySemaphore::ReleaseFromISR()
{
	Release();
}

void base::BinarySemaphore::Acquire()
{
	_bs.acquire();
}

bool base::BinarySemaphore::TryAcquire(base::Seconds const &timeout)
{
	return _bs.try_acquire_for(static_cast<std::chrono::nanoseconds>(timeout));
}

#endif

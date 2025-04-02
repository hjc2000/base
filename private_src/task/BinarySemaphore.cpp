#include "BinarySemaphore.h"
#include "base/string/define.h"
#include "base/unit/Nanoseconds.h"
#include "base/unit/Seconds.h"
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
	if (timeout < base::Seconds{0})
	{
		throw std::invalid_argument{CODE_POS_STR + "超时时间不能 <= 0."};
	}

	return _bs.try_acquire_for(static_cast<std::chrono::nanoseconds>(timeout));
}

#endif

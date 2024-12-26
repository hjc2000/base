#include "StdMutex.h"

#if HAS_THREAD

void base::StdMutex::Lock()
{
	_lock.lock();
}

void base::StdMutex::Unlock()
{
	_lock.unlock();
}

#endif

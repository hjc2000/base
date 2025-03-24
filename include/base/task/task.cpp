#include "task.h"
#include <thread>

#if HAS_THREAD

void base::task::Run(std::function<void()> func)
{
	std::thread{func}.detach();
}

#endif

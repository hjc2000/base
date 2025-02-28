#include "ISemaphore.h"

void base::ISemaphore::Release()
{
	Release(1);
}

#if HAS_THREAD
	#include <DisposableSemaphore.h>

std::shared_ptr<base::ISemaphore> base::di::CreateISemaphore(int32_t initial_count)
{
	return std::shared_ptr<base::ISemaphore>{new base::DisposableSemaphore{initial_count}};
}

#endif // HAS_THREAD

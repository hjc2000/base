#include "ISemaphore.h"
#include "DisposableSemaphore.h"

#if HAS_THREAD

std::shared_ptr<base::ISemaphore> base::CreateISemaphore(int32_t initial_count)
{
	return std::shared_ptr<base::ISemaphore>{new base::DisposableSemaphore{initial_count}};
}

#endif // HAS_THREAD

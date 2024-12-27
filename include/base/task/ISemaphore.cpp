#include "ISemaphore.h"

#if HAS_THREAD
#include <DisposableSemaphore.h>

std::shared_ptr<base::ISemaphore> base::di::CreateSemaphore(int initial_count)
{
	return std::shared_ptr<base::ISemaphore>{new base::DisposableSemaphore{initial_count}};
}

#endif // HAS_THREAD

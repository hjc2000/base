#include "ISemaphore.h"

#if HAS_THREAD
#include <DisposableSemaphore.h>

std::shared_ptr<base::ISemaphore> base::di::CreateSemaphore(int32_t initial_count)
{
	return std::shared_ptr<base::ISemaphore>{
		new base::DisposableSemaphore{
			base::DisposableSemaphore_InitialCount{initial_count},
		},
	};
}

#endif // HAS_THREAD

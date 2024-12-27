#include "IDisposableSemaphore.h"

#if HAS_THREAD
#include <DisposableSemaphore.h>

std::shared_ptr<base::IDisposableSemaphore>
base::di::CreateDisposableSemaphore(int32_t max_count, int32_t initial_count)
{
	return std::shared_ptr<base::IDisposableSemaphore>{
		new base::DisposableSemaphore{
			base::DisposableSemaphore_MaxCount{max_count},
			base::DisposableSemaphore_InitialCount{initial_count},
		},
	};
}

#endif // HAS_THREAD

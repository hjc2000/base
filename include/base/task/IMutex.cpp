#include "IMutex.h"
#ifndef HAS_THREAD
#define HAS_THREAD 0
#endif

#if HAS_THREAD
std::shared_ptr<base::IMutex> base::di::CreateMutex()
{
	return std::shared_ptr<base::IMutex>();
}
#endif

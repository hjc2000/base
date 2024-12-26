#include "IMutex.h"
#ifndef HAS_THREAD
#define HAS_THREAD 0
#endif

#if HAS_THREAD

#include <StdMutex.h>

std::shared_ptr<base::IMutex> base::di::CreateMutex()
{
	return std::shared_ptr<base::IMutex>{new base::StdMutex{}};
}

#endif

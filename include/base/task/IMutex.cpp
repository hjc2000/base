#include "IMutex.h"

#if HAS_THREAD

	#include <StdMutex.h>

std::shared_ptr<base::IMutex> base::di::CreateIMutex()
{
	return std::shared_ptr<base::IMutex>{new base::StdMutex{}};
}

#endif

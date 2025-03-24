#include "IMutex.h"
#include "StdMutex.h"

#if HAS_THREAD

std::shared_ptr<base::IMutex> base::CreateIMutex()
{
	return std::shared_ptr<base::IMutex>{new base::StdMutex{}};
}

#endif

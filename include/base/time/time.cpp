#include "time.h"

#if HAS_THREAD

std::chrono::nanoseconds base::time::TimeSinceEpoch()
{
	return std::chrono::nanoseconds();
}

#endif

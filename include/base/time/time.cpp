#include "time.h"

#if HAS_THREAD

base::TimePointSinceEpoch base::time::Now()
{
	// epoch 时刻是指 1970 年 1 月 1 日 00:00:00 UTC。
	std::chrono::duration since_epoch = std::chrono::system_clock::now().time_since_epoch();
	return base::TimePointSinceEpoch{std::chrono::duration_cast<std::chrono::nanoseconds>(since_epoch)};
}

#endif

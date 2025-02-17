#include "DateTime.h"

#if HAS_THREAD

int64_t base::DateTime::GetRealTimeInMilliseconds()
{
	// epoch 时刻是指 1970 年 1 月 1 日 00:00:00 UTC。
	std::chrono::duration since_epoch = std::chrono::system_clock::now().time_since_epoch();
	int64_t millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch).count();
	return millis;
}

int64_t base::DateTime::GetSteadyTimeInMilliseconds()
{
	// epoch 时刻是指 1970 年 1 月 1 日 00:00:00 UTC。
	std::chrono::duration now = std::chrono::steady_clock::now().time_since_epoch();
	int64_t now_in_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
	return now_in_milliseconds;
}

#endif // HAS_THREAD

#include "DateTime.h"

#if HAS_THREAD

int64_t base::DateTime::GetRealTimeInMilliseconds()
{
	std::chrono::duration since_epoch = std::chrono::system_clock::now().time_since_epoch();
	int64_t millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch).count();
	return millis;
}

int64_t base::DateTime::GetSteadyTimeInMilliseconds()
{
	std::chrono::duration now = std::chrono::steady_clock::now().time_since_epoch();
	int64_t now_in_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
	return now_in_milliseconds;
}

#endif // HAS_THREAD

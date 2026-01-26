#include "time.h" // IWYU pragma: keep

#if HAS_THREAD

	#include <pthread_time.h>

void base::time::SetRealTime(base::TimePointSinceEpoch const &value)
{
	timespec ts = static_cast<timespec>(value);

	// 设置系统时间
	int result = clock_settime(CLOCK_REALTIME, &ts);

	if (result != 0)
	{
		throw std::runtime_error{"设置系统时间失败，请检查是否是管理员权限。"};
	}
}

#endif

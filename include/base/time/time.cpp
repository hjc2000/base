#include "time.h" // IWYU pragma: keep

#if HAS_THREAD

	#include <pthread_time.h>

base::TimePointSinceEpoch base::time::Now()
{
	// epoch 时刻是指 1970 年 1 月 1 日 00:00:00 UTC。
	return base::TimePointSinceEpoch{std::chrono::system_clock::now().time_since_epoch()};
}

base::TimePointSinceEpoch base::time::SteadyClockNow()
{
	// epoch 时刻是指 1970 年 1 月 1 日 00:00:00 UTC。
	return base::TimePointSinceEpoch{std::chrono::steady_clock::now().time_since_epoch()};
}

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

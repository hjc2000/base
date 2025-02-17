#include "time.h"

#if HAS_THREAD

base::TimePointSinceEpoch base::time::Now()
{
	// epoch 时刻是指 1970 年 1 月 1 日 00:00:00 UTC。
	std::chrono::duration now = std::chrono::system_clock::now().time_since_epoch();
	return base::TimePointSinceEpoch{std::chrono::duration_cast<std::chrono::nanoseconds>(now)};
}

base::TimePointSinceEpoch base::time::SteadyClockNow()
{
	// epoch 时刻是指 1970 年 1 月 1 日 00:00:00 UTC。
	std::chrono::duration now = std::chrono::steady_clock::now().time_since_epoch();
	return base::TimePointSinceEpoch{std::chrono::duration_cast<std::chrono::nanoseconds>(now)};
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

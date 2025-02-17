#if HAS_THREAD

#include "TimeInterpolator.h"
#include <base/time/time.h>

int64_t base::TimeInterpolator::DeltaTimeInMilliseconds()
{
	if (_paused)
	{
		return _delta_time_when_pausing_in_milliseconds;
	}

	return static_cast<std::chrono::milliseconds>(base::time::SteadyClockNow()).count() - _time_at_sync_in_milliseconds;
}

void base::TimeInterpolator::SyncTime(int64_t now_time_in_milliseconds)
{
	_paused = false;
	_time_at_sync_in_milliseconds = static_cast<std::chrono::milliseconds>(base::time::SteadyClockNow()).count();
	_stepping_time_in_milliseconds = now_time_in_milliseconds;
	_delta_time_when_pausing_in_milliseconds = 0;
}

int64_t base::TimeInterpolator::InterpolatedTimeInMilliseconds()
{
	return _stepping_time_in_milliseconds + DeltaTimeInMilliseconds();
}

void base::TimeInterpolator::Pause()
{
	_paused = true;

	/* 记录当前的时间差，然后直到取消暂停前，让 DeltaTimeInMilliseconds 方法一直返回
	 * _delta_time_when_pausing_in_milliseconds。
	 */
	_delta_time_when_pausing_in_milliseconds = static_cast<std::chrono::milliseconds>(base::time::SteadyClockNow()).count() - _time_at_sync_in_milliseconds;
}

#endif // HAS_THREAD

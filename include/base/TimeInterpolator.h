#pragma once
#ifndef HAS_THREAD
#define HAS_THREAD 0
#endif

#if HAS_THREAD

#include <stdint.h>

namespace base
{
	/// @brief 时间插值器。
	class TimeInterpolator final
	{
	private:
		/// @brief 每次调用 SyncTime 方法就会捕获当前世界时间的毫秒数存到此字段。
		int64_t _time_at_sync_in_milliseconds = 0;

		/// @brief 步长较大的时间，在 SyncTime 方法中被设置。此时间需要被插值。
		int64_t _stepping_time_in_milliseconds = 0;

		bool _paused = true;

		/// @brief 当时间被暂停时，DeltaTimeInMilliseconds 方法返回此值，
		/// 而不是返回当前世界时间减去 _time_at_sync_in_milliseconds
		int64_t _delta_time_when_pausing_in_milliseconds = 0;

		/// @brief 当前时刻（调用本方法的时刻）距离上一次 SyncTime 过去了多久。
		/// @return
		int64_t DeltaTimeInMilliseconds();

	public:
		/// @brief 将时间插值器的时间同步到 now_time_in_milliseconds，即当前时间。
		/// @param now_time_in_milliseconds 当前时间。
		/// @note 时间插值器的时间将被同步到 now_time_in_milliseconds。
		void SyncTime(int64_t now_time_in_milliseconds);

		int64_t InterpolatedTimeInMilliseconds();

		void Pause();
	};
}

#endif // HAS_THREAD

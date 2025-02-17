#pragma once
#include <base/time/TimePointSinceEpoch.h>

namespace base
{
	namespace time
	{
		/// @brief 获取当前时刻。
		/// @return
		base::TimePointSinceEpoch Now();

		/// @brief 获取稳定时钟的当前时刻。
		/// @return
		base::TimePointSinceEpoch SteadyClockNow();
	} // namespace time
} // namespace base

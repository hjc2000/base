#pragma once
#include "base/time/TimePointSinceEpoch.h"
#include "DateTime.h"

namespace base::time
{
	///
	/// @brief 获取当前时刻。
	///
	/// @return
	///
	inline base::TimePointSinceEpoch Now()
	{
		// epoch 时刻是指 1970 年 1 月 1 日 00:00:00 UTC。
		return base::TimePointSinceEpoch{std::chrono::system_clock::now().time_since_epoch()};
	}

	///
	/// @brief 获取当前的日期时间。
	///
	/// @return
	///
	inline base::DateTime NowDateTime()
	{
		return base::DateTime{Now()};
	}

	///
	/// @brief 获取稳定时钟的当前时刻。
	///
	/// @return
	///
	inline base::TimePointSinceEpoch SteadyClockNow()
	{
		// epoch 时刻是指 1970 年 1 月 1 日 00:00:00 UTC。
		return base::TimePointSinceEpoch{std::chrono::steady_clock::now().time_since_epoch()};
	}

	///
	/// @brief 设置系统的时间。
	///
	/// @note 需要管理员权限。
	/// @note 操作系统自带时区功能，所以设置时间时不要手动处理时区带来的时间偏移。
	///
	/// @param value
	///
	void SetRealTime(base::TimePointSinceEpoch const &value);

} // namespace base::time

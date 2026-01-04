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
	base::TimePointSinceEpoch Now();

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
	base::TimePointSinceEpoch SteadyClockNow();

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

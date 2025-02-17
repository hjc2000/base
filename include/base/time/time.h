#pragma once
#include <chrono>
#include <ctime>

namespace base
{
	namespace time
	{
		/// @brief 从 epoch 时间开始到现在的时间间隔。
		/// @note epoch 时刻是指 1970 年 1 月 1 日 00:00:00 UTC。
		/// @return
		std::chrono::nanoseconds TimeSinceEpoch();
	} // namespace time
} // namespace base

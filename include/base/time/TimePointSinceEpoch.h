#pragma once
#include <chrono>
#include <ctime>

namespace base
{
	/// @brief 以 epoch 时刻作为零点的时刻。
	/// @note epoch 时刻是指 1970 年 1 月 1 日 00:00:00 UTC。
	/// @note 时刻就像电势那样没有绝对零点，只能选定一个参考的零点。电路中通常选择电源负极作为电势零点，
	/// 本类选择 epoch 时刻作为时刻的零点。
	class TimePointSinceEpoch
	{
	private:
		std::chrono::nanoseconds _time_since_epoch;

	public:
		/// @brief 无参构造。构造出来的时间刚好就是 epoch 时刻。
		/// @note epoch 时刻是指 1970 年 1 月 1 日 00:00:00 UTC。
		TimePointSinceEpoch();
	};
} // namespace base

#pragma once
#include <base/time/TimeSpan.h>

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

		explicit TimePointSinceEpoch(std::chrono::nanoseconds const &value);
		explicit TimePointSinceEpoch(std::chrono::microseconds const &value);
		explicit TimePointSinceEpoch(std::chrono::seconds const &value);

		explicit operator std::chrono::nanoseconds() const;
		explicit operator std::chrono::microseconds() const;
		explicit operator std::chrono::seconds() const;
		explicit operator timespec() const;

		/// @brief 两个时刻相减，得到时间段。
		/// @param rhs
		/// @return
		base::TimeSpan operator-(base::TimePointSinceEpoch const &rhs) const;

		/// @brief 时刻加上一个时间段，得到新的时刻。
		/// @param rhs
		/// @return
		base::TimePointSinceEpoch operator+(base::TimeSpan const &rhs) const;

		/// @brief 时刻减去一个时间段，得到新的时刻。
		/// @param rhs
		/// @return
		base::TimePointSinceEpoch operator-(base::TimeSpan const &rhs) const;
	};
} // namespace base

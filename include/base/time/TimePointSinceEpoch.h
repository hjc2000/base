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
		std::chrono::nanoseconds _time_since_epoch{};

	public:
#pragma region 构造函数
		/// @brief 无参构造。构造出来的时间刚好就是 epoch 时刻。
		/// @note epoch 时刻是指 1970 年 1 月 1 日 00:00:00 UTC。
		TimePointSinceEpoch();

		explicit TimePointSinceEpoch(std::chrono::nanoseconds const &value);
		explicit TimePointSinceEpoch(std::chrono::microseconds const &value);
		explicit TimePointSinceEpoch(std::chrono::milliseconds const &value);
		explicit TimePointSinceEpoch(std::chrono::seconds const &value);
		explicit TimePointSinceEpoch(timespec const &value);
#pragma endregion

#pragma region HAS_THREAD 限定构造函数
#if HAS_THREAD
		TimePointSinceEpoch(std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> const &value);
		TimePointSinceEpoch(std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds> const &value);
		TimePointSinceEpoch(std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> const &value);
		TimePointSinceEpoch(std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> const &value);
#endif
#pragma endregion

#pragma region 数据转换
		explicit operator std::chrono::nanoseconds() const;
		explicit operator std::chrono::microseconds() const;
		explicit operator std::chrono::milliseconds() const;
		explicit operator std::chrono::seconds() const;
		explicit operator timespec() const;
#pragma endregion

#pragma region HAS_THREAD 限定数据转换
#if HAS_THREAD
		operator std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>() const;
		operator std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds>() const;
		operator std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>() const;
		operator std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>() const;

		operator std::chrono::zoned_time<std::chrono::nanoseconds>() const;
		operator std::chrono::zoned_time<std::chrono::microseconds>() const;
		operator std::chrono::zoned_time<std::chrono::milliseconds>() const;
		operator std::chrono::zoned_time<std::chrono::seconds>() const;

		std::chrono::zoned_time<std::chrono::nanoseconds> ToNanosecondsZonedTime() const;
		std::chrono::zoned_time<std::chrono::microseconds> ToMicrosecondsZonedTime() const;
		std::chrono::zoned_time<std::chrono::milliseconds> ToMillisecondsZonedTime() const;
		std::chrono::zoned_time<std::chrono::seconds> ToSecondsZonedTime() const;

		std::string NanosecondsZonedTimeString() const;
		std::string MicrosecondsZonedTimeString() const;
		std::string MillisecondsZonedTimeString() const;
		std::string SecondsZonedTimeString() const;
#endif
#pragma endregion

#pragma region 四则运算符
		/// @brief 两个时刻相加没有物理意义。
		/// @param rhs
		/// @return
		base::TimeSpan operator+(base::TimePointSinceEpoch const &rhs) const = delete;

		/// @brief 两个时刻相减，得到时间段。
		/// @param rhs
		/// @return
		base::TimeSpan operator-(base::TimePointSinceEpoch const &rhs) const;

		/// @brief 时刻加上一个时间段，得到新的时刻。
		/// @param rhs
		/// @return
		base::TimePointSinceEpoch operator+(base::TimeSpan const &rhs) const;
		base::TimePointSinceEpoch &operator+=(base::TimeSpan const &rhs);

		/// @brief 时刻减去一个时间段，得到新的时刻。
		/// @param rhs
		/// @return
		base::TimePointSinceEpoch operator-(base::TimeSpan const &rhs) const;
		base::TimePointSinceEpoch &operator-=(base::TimeSpan const &rhs);

		base::TimePointSinceEpoch operator*(int64_t value) const;
		base::TimePointSinceEpoch &operator*=(int64_t value);
#pragma endregion
	};
} // namespace base

base::TimePointSinceEpoch operator*(int64_t left, base::TimePointSinceEpoch const &right);

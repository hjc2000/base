#pragma once
#include <chrono>
#include <ctime>

namespace base
{
	class TimePointSinceEpoch;

	class TimeSpan
	{
	private:
		std::chrono::nanoseconds _span{};

	public:
		TimeSpan();

		explicit TimeSpan(std::chrono::nanoseconds const &value);
		explicit TimeSpan(std::chrono::microseconds const &value);
		explicit TimeSpan(std::chrono::milliseconds const &value);
		explicit TimeSpan(std::chrono::seconds const &value);
		explicit TimeSpan(timespec const &value);

		explicit operator std::chrono::nanoseconds() const;
		explicit operator std::chrono::microseconds() const;
		explicit operator std::chrono::milliseconds() const;
		explicit operator std::chrono::seconds() const;
		explicit operator timespec() const;

#pragma region 四则运算符
		/// @brief 两个时间段相加，变成一个新的时间段。
		/// @param rhs
		/// @return
		base::TimeSpan operator+(base::TimeSpan const &rhs) const;

		/// @brief 两个时间段相减，得到一个新的时间段。
		/// @param rhs
		/// @return
		base::TimeSpan operator-(base::TimeSpan const &rhs) const;

		/// @brief 时间段加上时刻没有物理意义。
		/// @note 这里的主语是 “时间段” 。只有时刻加上时间段才有物理意义，即只能 “时刻” 作主语。
		/// @param rhs
		/// @return
		base::TimeSpan operator+(base::TimePointSinceEpoch const &rhs) const = delete;

		/// @brief 时间段减去时刻没有物理意义。
		/// @note 这里的主语是 “时间段” 。只有时刻减去时间段才有物理意义，即只能 “时刻” 作主语。
		/// @param rhs
		/// @return
		base::TimeSpan operator-(base::TimePointSinceEpoch const &rhs) const = delete;

		base::TimeSpan operator*(int64_t value) const;
		base::TimeSpan &operator*=(int64_t value);
#pragma endregion
	};
} // namespace base

base::TimeSpan operator*(int64_t left, base::TimeSpan const &right);

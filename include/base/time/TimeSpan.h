#pragma once
#include <chrono>
#include <ctime>

namespace base
{
	class TimePointSinceEpoch;

	/**
	 * @brief 时间片。
	 *
	 */
	class TimeSpan
	{
	private:
		std::chrono::nanoseconds _span{};

	public:
		// 构造函数

		TimeSpan();
		explicit TimeSpan(std::chrono::nanoseconds const &value);
		explicit TimeSpan(std::chrono::microseconds const &value);
		explicit TimeSpan(std::chrono::milliseconds const &value);
		explicit TimeSpan(std::chrono::seconds const &value);
		explicit TimeSpan(timespec const &value);

	public:
		// 转换

		explicit operator std::chrono::nanoseconds() const;
		explicit operator std::chrono::microseconds() const;
		explicit operator std::chrono::milliseconds() const;
		explicit operator std::chrono::seconds() const;
		explicit operator timespec() const;

	public:
		// 四则运算

		/**
		 * @brief 两个时间段相加，得到一个新的时间段。
		 *
		 * @param rhs
		 * @return base::TimeSpan
		 */
		base::TimeSpan operator+(base::TimeSpan const &rhs) const;

		/**
		 * @brief 将本时间段加上另一个时间段。
		 *
		 * @param rhs
		 * @return base::TimeSpan&
		 */
		base::TimeSpan &operator+=(base::TimeSpan const &rhs);

		/**
		 * @brief 两个时间段相减，得到一个新的时间段。
		 *
		 * @param rhs
		 * @return base::TimeSpan
		 */
		base::TimeSpan operator-(base::TimeSpan const &rhs) const;

		/**
		 * @brief 将本时间段减去另一个时间段。
		 *
		 * @param rhs
		 * @return base::TimeSpan&
		 */
		base::TimeSpan &operator-=(base::TimeSpan const &rhs);

		/**
		 * @brief 时间段加上时刻没有物理意义。
		 *
		 * @note 这里的主语是 “时间段” 。只有时刻加上时间段才有物理意义，即只能 “时刻” 作主语。
		 *
		 * @param rhs
		 * @return base::TimeSpan
		 */
		base::TimeSpan operator+(base::TimePointSinceEpoch const &rhs) const = delete;

		/**
		 * @brief 时间段减去时刻没有物理意义。
		 *
		 * @note 这里的主语是 “时间段” 。只有时刻减去时间段才有物理意义，即只能 “时刻” 作主语。
		 *
		 * @param rhs
		 * @return base::TimeSpan
		 */
		base::TimeSpan operator-(base::TimePointSinceEpoch const &rhs) const = delete;

		/**
		 * @brief 将时间段乘上一个系数进行缩放，得到一个新的时间段。
		 *
		 * @param value
		 * @return base::TimeSpan
		 */
		base::TimeSpan operator*(int64_t value) const;

		/**
		 * @brief 将本时间段乘上一个系数进行缩放。
		 *
		 * @param value
		 * @return base::TimeSpan&
		 */
		base::TimeSpan &operator*=(int64_t value);

	public:
		bool operator==(base::TimeSpan const &another) const;
		bool operator<(base::TimeSpan const &another) const;
		bool operator>(base::TimeSpan const &another) const;
		bool operator<=(base::TimeSpan const &another) const;
		bool operator>=(base::TimeSpan const &another) const;
	};
} // namespace base

base::TimeSpan operator*(int64_t left, base::TimeSpan const &right);

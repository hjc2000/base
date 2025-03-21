#pragma once
#include <chrono>
#include <cstdint>
#include <ctime>

namespace base
{
	class TimePointSinceEpoch;

	///
	/// @brief 时间片。
	///
	///
	class TimeSpan
	{
	private:
		std::chrono::nanoseconds _span{};

	public:
		/* #region 构造函数 */
		TimeSpan();
		explicit TimeSpan(std::chrono::nanoseconds const &value);
		explicit TimeSpan(std::chrono::microseconds const &value);
		explicit TimeSpan(std::chrono::milliseconds const &value);
		explicit TimeSpan(std::chrono::seconds const &value);
		explicit TimeSpan(timespec const &value);
		/* #endregion */

		explicit operator std::chrono::nanoseconds() const;
		explicit operator std::chrono::microseconds() const;
		explicit operator std::chrono::milliseconds() const;
		explicit operator std::chrono::seconds() const;
		explicit operator timespec() const;

		/* #region 四则运算 */

		///
		/// @brief 将本时间段加上另一个时间段。
		///
		/// @param rhs
		/// @return base::TimeSpan
		///
		base::TimeSpan operator+(base::TimeSpan const &rhs) const;

		///
		/// @brief 将本时间段加上另一个时间段。
		///
		/// @param rhs
		/// @return base::TimeSpan&
		///
		base::TimeSpan &operator+=(base::TimeSpan const &rhs);

		///
		/// @brief 将本时间段减去另一个时间段。
		///
		/// @param rhs
		/// @return base::TimeSpan
		///
		base::TimeSpan operator-(base::TimeSpan const &rhs) const;

		///
		/// @brief 将本时间段减去另一个时间段。
		///
		/// @param rhs
		/// @return base::TimeSpan&
		///
		base::TimeSpan &operator-=(base::TimeSpan const &rhs);

		///
		/// @brief 将本时间段乘上一个系数进行放大。
		///
		/// @param value
		/// @return base::TimeSpan
		///
		base::TimeSpan operator*(int64_t value) const;

		///
		/// @brief 将本时间段乘上一个系数进行放大。
		///
		/// @param value
		/// @return base::TimeSpan&
		///
		base::TimeSpan &operator*=(int64_t value);

		///
		/// @brief 将本时间段除以一个系数进行缩小。
		///
		/// @param value
		/// @return base::TimeSpan
		///
		base::TimeSpan operator/(int64_t value) const;

		///
		/// @brief 将本时间段除以一个系数进行缩小。
		///
		/// @param value
		/// @return base::TimeSpan&
		///
		base::TimeSpan &operator/=(int64_t value);

		/* #endregion */

		bool operator==(base::TimeSpan const &another) const;
		bool operator<(base::TimeSpan const &another) const;
		bool operator>(base::TimeSpan const &another) const;
		bool operator<=(base::TimeSpan const &another) const;
		bool operator>=(base::TimeSpan const &another) const;
	};
} // namespace base

base::TimeSpan operator*(int64_t left, base::TimeSpan const &right);

#pragma once
#include <chrono>
#include <ctime>

namespace base
{
	///
	/// @brief 时间片。
	///
	class TimeSpan
	{
	private:
		std::chrono::nanoseconds _span{};

	public:
		/* #region 构造函数 */

		constexpr TimeSpan() = default;

		constexpr explicit TimeSpan(std::chrono::nanoseconds const &value)
		{
			_span = value;
		}

		constexpr explicit TimeSpan(std::chrono::microseconds const &value)
		{
			_span = std::chrono::nanoseconds{value};
		}

		constexpr explicit TimeSpan(std::chrono::milliseconds const &value)
		{
			_span = std::chrono::nanoseconds{value};
		}

		constexpr explicit TimeSpan(std::chrono::seconds const &value)
		{
			_span = std::chrono::nanoseconds{value};
		}

		constexpr explicit TimeSpan(timespec const &value)
		{
			_span = std::chrono::seconds{value.tv_sec} + std::chrono::nanoseconds{value.tv_nsec};
		}

		/* #endregion */

		/* #region 强制转换 */

		constexpr explicit operator std::chrono::nanoseconds() const
		{
			return _span;
		}

		constexpr explicit operator std::chrono::microseconds() const
		{
			return std::chrono::duration_cast<std::chrono::microseconds>(_span);
		}

		constexpr explicit operator std::chrono::milliseconds() const
		{
			return std::chrono::duration_cast<std::chrono::milliseconds>(_span);
		}

		constexpr explicit operator std::chrono::seconds() const
		{
			return std::chrono::duration_cast<std::chrono::seconds>(_span);
		}

		constexpr explicit operator timespec() const
		{
			timespec ts{};
			std::chrono::seconds seconds_part = std::chrono::duration_cast<std::chrono::seconds>(_span);
			std::chrono::nanoseconds nanoseconds_part = _span - std::chrono::nanoseconds{seconds_part};

			// 整秒部分
			ts.tv_sec = static_cast<decltype(ts.tv_sec)>(seconds_part.count());

			// 纳秒部分
			ts.tv_nsec = static_cast<decltype(ts.tv_nsec)>(nanoseconds_part.count());
			return ts;
		}

		/* #endregion */

		/* #region 四则运算 */

		///
		/// @brief 将本时间段加上另一个时间段。
		///
		/// @param rhs
		/// @return
		///
		constexpr base::TimeSpan operator+(base::TimeSpan const &rhs) const
		{
			return base::TimeSpan{_span + rhs._span};
		}

		///
		/// @brief 将本时间段减去另一个时间段。
		///
		/// @param rhs
		/// @return
		///
		constexpr base::TimeSpan operator-(base::TimeSpan const &rhs) const
		{
			return base::TimeSpan{_span - rhs._span};
		}

		///
		/// @brief 将本时间段乘上一个系数进行放大。
		///
		/// @param value
		/// @return
		///
		template <typename RightType>
			requires(std::is_integral_v<RightType>)
		constexpr base::TimeSpan operator*(RightType value) const
		{
			return base::TimeSpan{std::chrono::nanoseconds{_span.count() * value}};
		}

		///
		/// @brief 将本时间段除以一个系数进行缩小。
		///
		/// @param value
		/// @return
		///
		template <typename RightType>
			requires(std::is_integral_v<RightType>)
		constexpr base::TimeSpan operator/(RightType value) const
		{
			return base::TimeSpan{std::chrono::nanoseconds{_span.count() / value}};
		}

		///
		/// @brief 将本时间段加上另一个时间段。
		///
		/// @param rhs
		/// @return
		///
		constexpr base::TimeSpan &operator+=(base::TimeSpan const &rhs)
		{
			_span += rhs._span;
			return *this;
		}

		///
		/// @brief 将本时间段减去另一个时间段。
		///
		/// @param rhs
		/// @return
		///
		constexpr base::TimeSpan &operator-=(base::TimeSpan const &rhs)
		{
			_span -= rhs._span;
			return *this;
		}

		///
		/// @brief 将本时间段乘上一个系数进行放大。
		///
		/// @param value
		/// @return
		///
		template <typename RightType>
			requires(std::is_integral_v<RightType>)
		constexpr base::TimeSpan &operator*=(RightType value)
		{
			_span = std::chrono::nanoseconds{_span.count() * value};
			return *this;
		}

		///
		/// @brief 将本时间段除以一个系数进行缩小。
		///
		/// @param value
		/// @return
		///
		template <typename RightType>
			requires(std::is_integral_v<RightType>)
		constexpr base::TimeSpan &operator/=(RightType value)
		{
			_span = std::chrono::nanoseconds{_span.count() / value};
			return *this;
		}

		/* #endregion */

		/* #region 比较 */

		constexpr bool operator==(base::TimeSpan const &another) const
		{
			return _span == another._span;
		}

		constexpr bool operator<(base::TimeSpan const &another) const
		{
			return _span < another._span;
		}

		constexpr bool operator>(base::TimeSpan const &another) const
		{
			return _span > another._span;
		}

		constexpr bool operator<=(base::TimeSpan const &another) const
		{
			return _span <= another._span;
		}

		constexpr bool operator>=(base::TimeSpan const &another) const
		{
			return _span >= another._span;
		}

		/* #endregion */
	};

} // namespace base

template <typename LeftType>
	requires(std::is_integral_v<LeftType>)
constexpr base::TimeSpan operator*(LeftType left, base::TimeSpan const &right)
{
	return right * left;
}

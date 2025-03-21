#pragma once
#include "base/string/ICanToString.h"
#include "base/time/converte.h"
#include "base/time/TimeSpan.h"
#include <chrono>

namespace base
{
	///
	/// @brief 以 epoch 时刻作为零点的时刻。
	///
	/// @note epoch 时刻是指 1970 年 1 月 1 日 00:00:00 UTC。
	///
	/// @note 时刻就像电势那样没有绝对零点，只能选定一个参考的零点。电路中通常选择电源负极作为电势零点，
	/// 本类选择 epoch 时刻作为时刻的零点。
	///
	class TimePointSinceEpoch :
		public base::ICanToString
	{
	private:
		std::chrono::nanoseconds _time_since_epoch{};

	public:
		/* #region 构造函数 */

		///
		/// @brief 参构造。构造出来的时间刚好就是 epoch 时刻。
		///
		/// @note epoch 时刻是指 1970 年 1 月 1 日 00:00:00 UTC。
		///
		TimePointSinceEpoch();

		explicit TimePointSinceEpoch(std::chrono::nanoseconds const &value);
		explicit TimePointSinceEpoch(std::chrono::microseconds const &value);
		explicit TimePointSinceEpoch(std::chrono::milliseconds const &value);
		explicit TimePointSinceEpoch(std::chrono::seconds const &value);
		explicit TimePointSinceEpoch(timespec const &value);

#if HAS_THREAD
		/* #region 从时间点构造 */
		explicit TimePointSinceEpoch(ns_time_point const &value);
		explicit TimePointSinceEpoch(us_time_point const &value);
		explicit TimePointSinceEpoch(ms_time_point const &value);
		explicit TimePointSinceEpoch(s_time_point const &value);
		explicit TimePointSinceEpoch(file_clock_time_point const &value);
		/* #endregion */
#endif

		/* #endregion */

		/* #region 强制转换 */
		explicit operator std::chrono::nanoseconds() const;
		explicit operator std::chrono::microseconds() const;
		explicit operator std::chrono::milliseconds() const;
		explicit operator std::chrono::seconds() const;
		explicit operator timespec() const;

		///
		/// @brief 强制转换为天数。
		///
		/// @note 天数 = 秒 / 60 / 60 / 24
		/// 标准库也只是进行了这种简单计算。闰秒，夏令时等问题应该是转换为 std::chrono::year_month_day
		/// 时才有考虑。
		///
		/// @return std::chrono::local_days
		///
		explicit operator std::chrono::local_days() const;

#if HAS_THREAD

		explicit operator std::chrono::year_month_day() const;

		/* #region 强制转换为时间点 */
		operator ns_time_point() const;
		operator us_time_point() const;
		operator ms_time_point() const;
		operator s_time_point() const;
		operator file_clock_time_point() const;
		/* #endregion */

		/* #region 强制转换为 zoned_time */
		operator ms_zoned_time() const;
		operator s_zoned_time() const;
		/* #endregion */
#endif
		/* #endregion */

		/* #region 四则运算 */

		///
		/// @brief 两个时刻相加没有物理意义。
		///
		/// @param rhs
		/// @return base::TimeSpan
		///
		base::TimeSpan operator+(base::TimePointSinceEpoch const &rhs) const = delete;

		///
		/// @brief 两个时刻相减，得到时间段。
		///
		/// @param rhs
		/// @return base::TimeSpan
		///
		base::TimeSpan operator-(base::TimePointSinceEpoch const &rhs) const;

		///
		/// @brief 时刻加上一个时间段，得到新的时刻。
		///
		/// @param rhs
		/// @return base::TimePointSinceEpoch
		///
		base::TimePointSinceEpoch operator+(base::TimeSpan const &rhs) const;

		///
		/// @brief 将本时刻加上一个时间段。
		///
		/// @param rhs
		/// @return base::TimePointSinceEpoch&
		///
		base::TimePointSinceEpoch &operator+=(base::TimeSpan const &rhs);

		///
		/// @brief 时刻减去一个时间段，得到新的时刻。
		///
		/// @param rhs
		/// @return base::TimePointSinceEpoch
		///
		base::TimePointSinceEpoch operator-(base::TimeSpan const &rhs) const;

		///
		/// @brief 将本时刻减去一个时间段。
		///
		/// @param rhs
		/// @return base::TimePointSinceEpoch&
		///
		base::TimePointSinceEpoch &operator-=(base::TimeSpan const &rhs);

		///
		/// @brief 将本时刻乘上一个系数进行缩放，得到新的时刻。
		///
		/// @param value
		/// @return base::TimePointSinceEpoch
		///
		base::TimePointSinceEpoch operator*(int64_t value) const;

		///
		/// @brief 将本时刻乘上一个系数进行缩放。
		///
		/// @param value
		/// @return base::TimePointSinceEpoch&
		///
		base::TimePointSinceEpoch &operator*=(int64_t value);
		/* #endregion */

		/* #region 比较 */
		bool operator==(base::TimePointSinceEpoch const &another) const;
		bool operator<(base::TimePointSinceEpoch const &another) const;
		bool operator>(base::TimePointSinceEpoch const &another) const;
		bool operator<=(base::TimePointSinceEpoch const &another) const;
		bool operator>=(base::TimePointSinceEpoch const &another) const;
		/* #endregion */

		/* #region 转化为字符串 */
#if HAS_THREAD
		/* #region 转换为区域时间字符串 */
		std::string NanosecondsZonedTimeString() const;
		std::string MicrosecondsZonedTimeString() const;
		std::string MillisecondsZonedTimeString() const;
		std::string SecondsZonedTimeString() const;
		/* #endregion */
#endif

		///
		/// @brief 转化为字符串。
		///
		/// @return std::string
		///
		virtual std::string ToString() const override;

		/* #endregion */
	};
} // namespace base

base::TimePointSinceEpoch operator*(int64_t left, base::TimePointSinceEpoch const &right);

#pragma once
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
	class TimePointSinceEpoch
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

		/* #endregion */

		/* #region 四则运算 */

		///
		/// @brief 两个时刻相减，得到时间段。
		///
		/// @param rhs
		/// @return base::TimeSpan
		///
		base::TimeSpan operator-(base::TimePointSinceEpoch const &rhs) const;

		///
		/// @brief 将本时刻加上一个时间段，得到新的时刻。
		///
		/// @param rhs
		/// @return base::TimePointSinceEpoch
		///
		base::TimePointSinceEpoch operator+(base::TimeSpan const &rhs) const;

		///
		/// @brief 将本时刻加上一个时间段，得到新的时刻。
		///
		/// @param rhs
		/// @return base::TimePointSinceEpoch&
		///
		base::TimePointSinceEpoch &operator+=(base::TimeSpan const &rhs);

		///
		/// @brief 将本时刻减去一个时间段，得到新的时刻。
		///
		/// @param rhs
		/// @return base::TimePointSinceEpoch
		///
		base::TimePointSinceEpoch operator-(base::TimeSpan const &rhs) const;

		///
		/// @brief 将本时刻减去一个时间段，得到新的时刻。
		///
		/// @param rhs
		/// @return base::TimePointSinceEpoch&
		///
		base::TimePointSinceEpoch &operator-=(base::TimeSpan const &rhs);

		/* #endregion */

		/* #region 比较 */
		bool operator==(base::TimePointSinceEpoch const &another) const;
		bool operator<(base::TimePointSinceEpoch const &another) const;
		bool operator>(base::TimePointSinceEpoch const &another) const;
		bool operator<=(base::TimePointSinceEpoch const &another) const;
		bool operator>=(base::TimePointSinceEpoch const &another) const;
		/* #endregion */
	};
} // namespace base

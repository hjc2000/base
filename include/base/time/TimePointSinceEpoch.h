#pragma once
#include "base/time/TimeSpan.h"
#include <chrono>
#include <filesystem>

namespace base
{
	/* #region 类型别名 */

	using ns_time_point = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;
	using us_time_point = std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds>;
	using ms_time_point = std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>;
	using s_time_point = std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>;
	using file_clock_time_point = decltype(std::filesystem::directory_entry{}.last_write_time());

	using ns_zoned_time = std::chrono::zoned_time<std::chrono::nanoseconds>;
	using us_zoned_time = std::chrono::zoned_time<std::chrono::microseconds>;
	using ms_zoned_time = std::chrono::zoned_time<std::chrono::milliseconds>;
	using s_zoned_time = std::chrono::zoned_time<std::chrono::seconds>;

	/* #endregion */

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
		/// @brief 无参构造。构造出来的时间刚好就是 epoch 时刻。
		///
		/// @note epoch 时刻是指 1970 年 1 月 1 日 00:00:00 UTC。
		///
		constexpr TimePointSinceEpoch() = default;

		constexpr explicit TimePointSinceEpoch(std::chrono::nanoseconds const &value)
		{
			_time_since_epoch = value;
		}

		constexpr explicit TimePointSinceEpoch(std::chrono::microseconds const &value)
		{
			_time_since_epoch = std::chrono::nanoseconds{value};
		}

		constexpr explicit TimePointSinceEpoch(std::chrono::milliseconds const &value)
		{
			_time_since_epoch = std::chrono::nanoseconds{value};
		}

		constexpr explicit TimePointSinceEpoch(std::chrono::seconds const &value)
		{
			_time_since_epoch = std::chrono::nanoseconds{value};
		}

		constexpr explicit TimePointSinceEpoch(timespec const &value)
		{
			_time_since_epoch = std::chrono::seconds{value.tv_sec} +
								std::chrono::nanoseconds{value.tv_nsec};
		}

		explicit TimePointSinceEpoch(file_clock_time_point const &value)
		{
			std::chrono::nanoseconds time_since_epoch = value.time_since_epoch();

			// 文件时钟不准，并不是当前的 epoch 时间，而是与 epoch 时间之间有一个固定的偏移量。
			// 获取这个偏移量，然后将文件时钟的时间戳加上偏移量就得到了文件时钟时间戳对应的 epoch 时间戳。
			auto delta = std::chrono::system_clock::now().time_since_epoch() -
						 std::filesystem::file_time_type::clock::now().time_since_epoch();

			time_since_epoch += delta;
			_time_since_epoch = time_since_epoch;
		}

		/* #endregion */

		/* #region 强制转换 */

		constexpr explicit operator std::chrono::nanoseconds() const
		{
			return _time_since_epoch;
		}

		constexpr explicit operator std::chrono::microseconds() const
		{
			return std::chrono::duration_cast<std::chrono::microseconds>(_time_since_epoch);
		}

		constexpr explicit operator std::chrono::milliseconds() const
		{
			return std::chrono::duration_cast<std::chrono::milliseconds>(_time_since_epoch);
		}

		constexpr explicit operator std::chrono::seconds() const
		{
			return std::chrono::duration_cast<std::chrono::seconds>(_time_since_epoch);
		}

		constexpr explicit operator base::ns_time_point() const
		{
			return ns_time_point{static_cast<std::chrono::nanoseconds>(*this)};
		}

		constexpr explicit operator base::us_time_point() const
		{
			return us_time_point{static_cast<std::chrono::microseconds>(*this)};
		}

		constexpr explicit operator base::ms_time_point() const
		{
			return ms_time_point{static_cast<std::chrono::milliseconds>(*this)};
		}

		constexpr explicit operator base::s_time_point() const
		{
			return s_time_point{static_cast<std::chrono::seconds>(*this)};
		}

		constexpr explicit operator timespec() const
		{
			timespec ts{};
			std::chrono::seconds seconds_part = std::chrono::duration_cast<std::chrono::seconds>(_time_since_epoch);
			std::chrono::nanoseconds nanoseconds_part = _time_since_epoch - std::chrono::nanoseconds{seconds_part};

			// 整秒部分
			ts.tv_sec = static_cast<decltype(ts.tv_sec)>(seconds_part.count());

			// 纳秒部分
			ts.tv_nsec = static_cast<decltype(ts.tv_nsec)>(nanoseconds_part.count());
			return ts;
		}

		///
		/// @brief 强制转换为天数。
		///
		/// @note 天数 = 秒 / 60 / 60 / 24
		/// 标准库也只是进行了这种简单计算。
		///
		/// @return
		///
		constexpr explicit operator std::chrono::local_days() const
		{
			using duration_type = decltype(std::chrono::local_days{}.time_since_epoch());
			duration_type duration = std::chrono::duration_cast<duration_type>(_time_since_epoch);
			std::chrono::local_days ret{duration};
			return ret;
		}

		constexpr explicit operator std::chrono::year_month_day() const
		{
			std::chrono::year_month_day ret{static_cast<std::chrono::local_days>(*this)};
			return ret;
		}

		/* #endregion */

		/* #region 四则运算 */

		///
		/// @brief 将本时刻加上一个时间段，得到新的时刻。
		///
		/// @param rhs
		///
		/// @return
		///
		constexpr base::TimePointSinceEpoch operator+(base::TimeSpan const &rhs) const
		{
			return base::TimePointSinceEpoch{_time_since_epoch + static_cast<std::chrono::nanoseconds>(rhs)};
		}

		///
		/// @brief 两个时刻相减，得到时间段。
		///
		/// @param rhs
		///
		/// @return
		///
		constexpr base::TimeSpan operator-(base::TimePointSinceEpoch const &rhs) const
		{
			return base::TimeSpan{_time_since_epoch - rhs._time_since_epoch};
		}

		///
		/// @brief 将本时刻减去一个时间段，得到新的时刻。
		///
		/// @param rhs
		///
		/// @return
		///
		constexpr base::TimePointSinceEpoch operator-(base::TimeSpan const &rhs) const
		{
			return base::TimePointSinceEpoch{_time_since_epoch - static_cast<std::chrono::nanoseconds>(rhs)};
		}

		///
		/// @brief 将本时刻加上一个时间段，得到新的时刻。
		///
		/// @param rhs
		///
		/// @return
		///
		constexpr base::TimePointSinceEpoch &operator+=(base::TimeSpan const &rhs)
		{
			_time_since_epoch += static_cast<std::chrono::nanoseconds>(rhs);
			return *this;
		}

		///
		/// @brief 将本时刻减去一个时间段，得到新的时刻。
		///
		/// @param rhs
		///
		/// @return
		///
		constexpr base::TimePointSinceEpoch &operator-=(base::TimeSpan const &rhs)
		{
			_time_since_epoch -= static_cast<std::chrono::nanoseconds>(rhs);
			return *this;
		}

		/* #endregion */

		/* #region 比较 */

		constexpr bool operator==(base::TimePointSinceEpoch const &another) const
		{
			return _time_since_epoch == another._time_since_epoch;
		}

		constexpr bool operator<(base::TimePointSinceEpoch const &another) const
		{
			return _time_since_epoch < another._time_since_epoch;
		}

		constexpr bool operator>(base::TimePointSinceEpoch const &another) const
		{
			return _time_since_epoch > another._time_since_epoch;
		}

		constexpr bool operator<=(base::TimePointSinceEpoch const &another) const
		{
			return _time_since_epoch <= another._time_since_epoch;
		}

		constexpr bool operator>=(base::TimePointSinceEpoch const &another) const
		{
			return _time_since_epoch >= another._time_since_epoch;
		}

		/* #endregion */
	};

} // namespace base

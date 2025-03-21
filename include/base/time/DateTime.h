#pragma once
#include "base/string/ICanToString.h"
#include <cstdint>

namespace base
{
	class TimePointSinceEpoch;

	class UtcHourOffset
	{
	private:
		int64_t _value{};

	public:
		UtcHourOffset() = default;

		explicit UtcHourOffset(int64_t value)
			: _value(value)
		{
		}

		int64_t Value() const
		{
			return _value;
		}
	};

	class DateTime :
		public base::ICanToString
	{
	private:
		int64_t _year{};
		int64_t _month{};
		int64_t _day{};
		int64_t _hour{};
		int64_t _minute{};
		int64_t _second{};
		int64_t _nanosecond{};
		int64_t _utc_hour_offset{};

		/* #region 检查 */
		void CheckMonth();
		void CheckDay();
		void CheckHour();
		void CheckMinute();
		void CheckSecond();
		void CheckNanosecond();
		/* #endregion */

		/* #region 私有时间调整方法 */

		///
		/// @brief 增加月。
		///
		/// @param value
		///
		void AddMonths(int64_t value);

		///
		/// @brief 以年为周期，将日索引调整到最小正周期内。
		///
		/// @param day_index
		///
		void AdjustDayIndexToOneYear(int64_t &day_index);

		///
		/// @brief 以月为周期，将日调整到最小正周期内。
		///
		/// @note 实际上月并不是狭义上的周期。按照广义上，可以理解为周期会变得周期函数。
		///
		/// @param day_index
		///
		void AdjustDayIndexToOneMonth(int64_t &day_index);

		///
		/// @brief 以日为周期，将小时索引调整到最小正周期内。
		///
		/// @param hour_index
		///
		void AdjustHourIndexToOneDay(int64_t &hour_index);

		///
		/// @brief 以小时为周期，将分钟索引调整到最小正周期内。
		///
		/// @param minute_index
		///
		void AdjustMinuteIndexToOneHour(int64_t &minute_index);

		///
		/// @brief 以分钟为周期，将秒调整到最小正周期内。
		///
		/// @param second_index
		///
		void AdjustSecondsIndexToOneMinute(int64_t &second_index);
		/* #endregion */

	public:
		/* #region 构造函数 */

		DateTime() = default;

		///
		/// @brief 通过 UTC + 0 的日期时间构造。
		///
		/// @param year
		/// @param month
		/// @param day
		/// @param hour
		/// @param minute
		/// @param second
		/// @param nanosecond
		///
		DateTime(int64_t year, int64_t month, int64_t day,
				 int64_t hour, int64_t minute, int64_t second,
				 int64_t nanosecond);

		///
		/// @brief 构造 UTC 偏移日期时间。
		///
		/// @param utc_hour_offset 你在下面输入的日期时间是 UTC 偏移多少小时。
		/// @param year
		/// @param month
		/// @param day
		/// @param hour
		/// @param minute
		/// @param second
		/// @param nanosecond
		///
		DateTime(base::UtcHourOffset utc_hour_offset,
				 int64_t year, int64_t month, int64_t day,
				 int64_t hour, int64_t minute, int64_t second,
				 int64_t nanosecond);

		///
		/// @brief 通过时间点构造。
		///
		/// @param time_point
		///
		DateTime(base::TimePointSinceEpoch const &time_point);

		///
		/// @brief 通过时间点构造一个 UTC 偏移的日期时间。
		///
		/// @param utc_hour_offset
		/// @param time_point
		///
		DateTime(base::UtcHourOffset utc_hour_offset,
				 base::TimePointSinceEpoch const &time_point);

		/* #endregion */

		/* #region 日期时间属性 */

		int64_t Year() const
		{
			return _year;
		}

		int64_t Month() const
		{
			return _month;
		}

		int64_t Day() const
		{
			return _day;
		}

		int64_t Hour() const
		{
			return _hour;
		}

		int64_t Minute() const
		{
			return _minute;
		}

		int64_t Second() const
		{
			return _second;
		}

		int64_t Nanosecond() const
		{
			return _nanosecond;
		}

		/* #endregion */

		///
		/// @brief 本年总共有多少天。
		///
		/// @return int64_t
		///
		int64_t CurrentYearDayCount();

		///
		/// @brief 本月份总共有多少天。
		///
		/// @return int64_t
		///
		int64_t CurrentMonthDayCount();

		///
		/// @brief 今年是否是闰年。
		///
		/// @return true
		/// @return false
		///
		bool IsLeapYear() const;

		/* #region 公共时间调整方法 */

		///
		/// @brief 增加日。
		///
		/// @param value
		///
		void AddDays(int64_t value);

		///
		/// @brief 增加小时。
		///
		/// @param value
		///
		void AddHours(int64_t value);

		///
		/// @brief 增加分钟。
		///
		/// @param value
		///
		void AddMinutes(int64_t value);

		///
		/// @brief 增加秒。
		///
		/// @param value
		///
		void AddSeconds(int64_t value);

		void AddNanoseconds(int64_t value);

		/* #endregion */

		///
		/// @brief 转化为字符串。
		///
		/// @note 本类储存的字段是 UTC + 0 的日期时间，但是在转换成字符串时，会加上偏移的
		/// 小时。例如构造函数设置 utc_hour_offset = 8，则本函数返回的是 UTC + 8 日期时
		/// 间的字符串。
		///
		/// @return std::string
		///
		virtual std::string ToString() const override;

		///
		/// @brief 强制转换为时间点。
		///
		/// @return base::TimePointSinceEpoch
		///
		operator base::TimePointSinceEpoch() const;

		/* #region 比较 */

		bool operator==(DateTime const &another) const;
		bool operator<(DateTime const &another) const;
		bool operator>(DateTime const &another) const;
		bool operator<=(DateTime const &another) const;
		bool operator>=(DateTime const &another) const;

		/* #endregion */

		///
		/// @brief epoch 起点。
		///
		/// @return base::DateTime
		///
		base::DateTime EpochStart() const
		{
			base::DateTime start{1970, 1, 1, 0, 0, 0, 0};
			return start;
		}
	};
} // namespace base

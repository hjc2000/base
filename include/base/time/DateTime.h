#pragma once
#include "base/define.h"
#include "base/string/ICanToString.h"
#include <cstdint>

namespace base
{
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

		void CheckMonth();
		void CheckDay();
		void CheckHour();
		void CheckMinute();
		void CheckSecond();
		void CheckNanosecond();

		///
		/// @brief 增加月。
		///
		/// @param value
		///
		void AddMonths(int64_t value);

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

		///
		/// @brief 绕过检查机制，构造一个本类对象。
		///
		/// @param year
		/// @param month
		/// @param day
		/// @param hour
		/// @param minute
		/// @param second
		/// @param nanosecond
		/// @return static_function
		///
		static_function base::DateTime CreateWithoutCheck(int64_t year, int64_t month, int64_t day,
														  int64_t hour, int64_t minute, int64_t second,
														  int64_t nanosecond);

		static_function int64_t CountLeapSecondsBetweenTwoMinutes(base::DateTime const &start, base::DateTime const &end);

	public:
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
		DateTime(int64_t utc_hour_offset,
				 int64_t year, int64_t month, int64_t day,
				 int64_t hour, int64_t minute, int64_t second,
				 int64_t nanosecond);

		/* #region 属性 */

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
		/// @brief 当前月份有多少天。
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

		/* #region 当前闰秒 */

		///
		/// @brief 当前月的闰秒。
		///
		/// @return int64_t 会返回 -1, 0, 1 三个值中的一个。
		///
		int64_t LeapSecondOfCurrentMonth() const;

		///
		/// @brief 当前日的闰秒。
		///
		/// @return int64_t 会返回 -1, 0, 1 三个值中的一个。
		///
		int64_t LeapSecondOfCurrentDay() const;

		///
		/// @brief 当前小时的闰秒。
		///
		/// @return int64_t 会返回 -1, 0, 1 三个值中的一个。
		///
		int64_t LeapSecondOfCurrentHour() const;

		///
		/// @brief 当前分钟的闰秒。
		///
		/// @return int64_t 会返回 -1, 0, 1 三个值中的一个。
		///
		int64_t LeapSecondOfCurrentMinute() const;
		/* #endregion */

		///
		/// @brief 增加秒。
		///
		/// @param value
		///
		void AddSeconds(int64_t value);

		///
		/// @brief 转化为字符串。
		///
		/// @return std::string
		///
		virtual std::string ToString() const override;

		/* #region 比较 */

		bool operator==(DateTime const &another) const;
		bool operator<(DateTime const &another) const;
		bool operator>(DateTime const &another) const;
		bool operator<=(DateTime const &another) const;
		bool operator>=(DateTime const &another) const;

		/* #endregion */
	};
} // namespace base

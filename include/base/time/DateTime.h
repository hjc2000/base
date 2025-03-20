#pragma once
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

		void CheckMonth();
		void CheckDay();
		void CheckHour();
		void CheckMinute();
		void CheckSecond();
		void CheckNanosecond();

		///
		/// @brief 将 day_index 加减一整年的天数，然后增加或减少年份，
		/// 将 day_index 调整到一年的天数以内。
		///
		/// @param day_index
		///
		void AddYearByDayIndex(int64_t &day_index);

	public:
		DateTime() = default;

		///
		/// @brief 通过 UTC + 0 的日期事件构造。
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

		int64_t LeapSecond() const;

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
		/// @brief 转化为字符串。
		///
		/// @return std::string
		///
		virtual std::string ToString() const override;
	};
} // namespace base

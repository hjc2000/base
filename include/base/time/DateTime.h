#pragma once
#include "base/string/ICanToString.h"
#include <cstdint>

namespace base
{
	enum class LeapSecondState
	{
		None,
		AddOneSecond,
		SubtractOneSecond,
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

		void CheckMonth();
		void CheckDay();
		void CheckHour();
		void CheckMinute();
		void CheckSecond();
		void CheckNanosecond();

	public:
		DateTime() = default;

		///
		/// @brief 通过 UTC+0 的日期事件构造。
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
		/// @brief 今年是否是闰年。
		///
		/// @return true
		/// @return false
		///
		bool IsLeapYear() const;

		///
		/// @brief 当前分钟的闰秒情况。
		///
		/// @return base::LeapSecondState
		///
		base::LeapSecondState LeapSecondState() const;

		void AddYear(int64_t value)
		{
			_year += value;
		}

		void AddMonth(int64_t value);

		///
		/// @brief 转化为字符串。
		///
		/// @return std::string
		///
		virtual std::string ToString() const override;
	};
} // namespace base

#pragma once
#include "base/string/define.h"
#include "base/string/String.h"
#include "base/time/convert.h"
#include "base/time/TimePointSinceEpoch.h"
#include "DateTimeStringBuilder.h"
#include "UtcHourOffset.h"
#include <array>
#include <bits/chrono.h>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <stdexcept>

namespace base
{
	class TimePointSinceEpoch;

	///
	/// @brief 日期时间。
	///
	/// @note 计算时始终认为日期时间是固定的规律，即考虑规律是固定的闰年，但不考虑闰秒。
	///
	class DateTime
	{
	private:
		/* #region 日期时间字段 */

		int64_t _year{};
		int64_t _month{};
		int64_t _day{};
		int64_t _hour{};
		int64_t _minute{};
		int64_t _second{};
		int64_t _nanosecond{};
		int64_t _utc_hour_offset{};

		/* #endregion */

		/* #region 检查 */

		constexpr void CheckMonth()
		{
			if (_month < 1 || _month > 12)
			{
				throw std::invalid_argument{CODE_POS_STR + "非法月份。"};
			}
		}

		constexpr void CheckDay()
		{
			if (_day < 1 || _day > CurrentMonthDayCount())
			{
				throw std::invalid_argument{CODE_POS_STR + "非法日。"};
			}
		}

		constexpr void CheckHour()
		{
			if (_hour < 0 || _hour > 23)
			{
				throw std::invalid_argument{CODE_POS_STR + "非法小时。"};
			}
		}

		constexpr void CheckMinute()
		{
			if (_minute < 0 || _minute > 59)
			{
				throw std::invalid_argument{CODE_POS_STR + "非法分钟。"};
			}
		}

		constexpr void CheckSecond()
		{
			if (_second < 0 || _second > 59)
			{
				throw std::invalid_argument{CODE_POS_STR + "非法秒。"};
			}
		}

		constexpr void CheckNanosecond()
		{
			if (_nanosecond < 0 || _nanosecond >= static_cast<int64_t>(1000) * 1000 * 1000)
			{
				throw std::invalid_argument{CODE_POS_STR + "非法纳秒。"};
			}
		}

		/* #endregion */

		/* #region 私有时间调整方法 */

		///
		/// @brief 增加月。
		///
		/// @param value
		///
		constexpr void AddMonths(int64_t value)
		{
			if (value == 0)
			{
				return;
			}

			int64_t month_index = _month - 1 + value;
			if (month_index >= 0 && month_index < 12)
			{
				// 在最小正周期内
				_month = month_index + 1;
				return;
			}

			// 不在最小正周期内
			_year += month_index / 12;
			month_index %= 12;
			if (month_index < 0)
			{
				_year -= 1;
				month_index += 12;
			}

			_month = month_index + 1;
		}

		///
		/// @brief 将日索引调整到一年的周期内。
		///
		/// @param day_index 日索引。如果日索引不在一年的周期内，会增大或减小年，并消耗日索引，
		/// 让日索引变到一年的周期内。
		///
		constexpr void AdjustDayIndexToOneYear(int64_t &day_index)
		{
			if (day_index >= 0 && day_index < CurrentYearDayCount())
			{
				// 以年为周期，已经处于最小正周期内了。
				return;
			}

			if (day_index > 0)
			{
				while (true)
				{
					int64_t current_year_day_count = CurrentYearDayCount();
					if (day_index < current_year_day_count)
					{
						return;
					}

					day_index -= current_year_day_count;
					_year += 1;
				}
			}

			// day_index < 0
			while (true)
			{
				// 前往去年
				_year -= 1;
				day_index += CurrentYearDayCount();
				if (day_index >= 0)
				{
					return;
				}
			}
		}

		///
		/// @brief 将日索引调整到一个月的周期内。
		///
		/// @param day_index
		///
		constexpr void AdjustDayIndexToOneMonth(int64_t &day_index)
		{
			AdjustDayIndexToOneYear(day_index);

			if (day_index >= 0 && day_index < CurrentMonthDayCount())
			{
				return;
			}

			if (day_index > 0)
			{
				while (true)
				{
					// 对于本月，当前的日的索引是 day_index 的当前值，如果要将索引起点调整到下一个月
					// 的 1 日，即坐标原点向右移动，则 day_index 躺枪，被平白无故变小了。
					//
					// 则 day_index 的值在新的坐标中要减去偏移量 day_index.
					int64_t current_month_day_count = CurrentMonthDayCount();
					if (day_index < current_month_day_count)
					{
						// 到不了下个月
						return;
					}

					day_index -= current_month_day_count;
					AddMonths(1);
				}
			}

			// 到这里说明 day_index < 0
			while (true)
			{
				// 前往上一个月
				AddMonths(-1);
				day_index += CurrentMonthDayCount();
				if (day_index >= 0)
				{
					return;
				}
			}
		}

		///
		/// @brief 以日为周期，将小时索引调整到最小正周期内。
		///
		/// @param hour_index
		///
		constexpr void AdjustHourIndexToOneDay(int64_t &hour_index)
		{
			if (hour_index >= 0 && hour_index < 24)
			{
				return;
			}

			AddDays(hour_index / 24);
			hour_index %= 24;

			if (hour_index < 0)
			{
				AddDays(-1);
				hour_index += 24;
			}
		}

		///
		/// @brief 以小时为周期，将分钟索引调整到最小正周期内。
		///
		/// @param minute_index
		///
		constexpr void AdjustMinuteIndexToOneHour(int64_t &minute_index)
		{
			if (minute_index >= 0 && minute_index < 60)
			{
				return;
			}

			AddHours(minute_index / 60);
			minute_index %= 60;
			if (minute_index < 0)
			{
				AddHours(-1);
				minute_index += 60;
			}
		}

		///
		/// @brief 以分钟为周期，将秒调整到最小正周期内。
		///
		/// @param second_index
		///
		void AdjustSecondsIndexToOneMinute(int64_t &second_index);

		/* #endregion */

		/* #region 不考虑时区转换为本地时区的日期时间字符串 */
		base::String YearString() const;
		base::String MonthString() const;
		base::String DayString() const;
		base::String HourString() const;
		base::String MinuteString() const;
		base::String SecondString() const;
		base::String NanosecondString() const;
		/* #endregion */

	public:
		/* #region 构造函数 */

		constexpr DateTime() = default;

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
		/// @param time_point 时间点。epoch 时间戳，与时区无关。
		///
		DateTime(base::TimePointSinceEpoch const &time_point);

		///
		/// @brief 通过时间点构造一个 UTC 偏移的日期时间。
		///
		/// @param utc_hour_offset 你所处的时区的 UTC 小时偏移量。
		/// @param time_point 时间点。epoch 时间戳，与时区无关。
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
		/// @return
		///
		constexpr int64_t CurrentYearDayCount()
		{
			if (IsLeapYear())
			{
				return 366;
			}

			return 365;
		}

		///
		/// @brief 本月份总共有多少天。
		///
		/// @return
		///
		constexpr int64_t CurrentMonthDayCount()
		{
			switch (_month)
			{
			case 2:
				{
					if (IsLeapYear())
					{
						return 29;
					}

					return 28;
				}
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				{
					return 31;
				}
			default:
				{
					return 30;
				}
			}
		}

		///
		/// @brief 今年是否是闰年。
		///
		/// @return
		///
		constexpr bool IsLeapYear() const
		{
			if (_year % 100 == 0)
			{
				// 整百年份必须被 400 整除才是闰年。
				return _year % 400 == 0;
			}

			// 非整百年份只要能被 4 整除就是闰年。
			return _year % 4 == 0;
		}

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

		///
		/// @brief 增加纳秒。
		///
		/// @param value
		///
		void AddNanoseconds(int64_t value);

		base::DateTime operator+(std::chrono::seconds const &value) const
		{
			base::DateTime ret{*this};
			ret += value;
			return ret;
		}

		base::DateTime &operator+=(std::chrono::seconds const &value)
		{
			AddSeconds(value.count());
			return *this;
		}

		/* #endregion */

		///
		/// @brief 强制转换为时间点。
		///
		/// @return
		///
		base::TimePointSinceEpoch TimePointSinceEpoch() const;

		///
		/// @brief 获取日期时间字符串构建器。
		///
		/// @note 不考虑时区。
		///
		/// @return
		///
		base::DateTimeStringBuilder DateTimeStringBuilder() const;

		///
		/// @brief 获取本地日期时间字符串构建器。
		///
		/// @note 考虑时区。
		///
		/// @return
		///
		base::DateTimeStringBuilder LocalDateTimeStringBuilder() const;

		/* #region 比较 */

		bool operator==(DateTime const &another) const;
		bool operator<(DateTime const &another) const;
		bool operator>(DateTime const &another) const;
		bool operator<=(DateTime const &another) const;
		bool operator>=(DateTime const &another) const;

		/* #endregion */

		///
		/// @brief epoch 起点日期。
		///
		/// @return
		///
		static base::DateTime EpochStart()
		{
			base::DateTime start{1970, 1, 1, 0, 0, 0, 0};
			return start;
		}
	};

#if HAS_THREAD
	namespace test
	{
		void TestDateTime();
	} // namespace test
#endif // HAS_THREAD

} // namespace base

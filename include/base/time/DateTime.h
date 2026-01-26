#pragma once
#include "base/string/define.h"
#include "base/string/String.h"
#include "base/time/DateTimeStringBuilder.h"
#include "base/time/TimePointSinceEpoch.h"
#include "base/time/UtcHourOffset.h"
#include <array>
#include <chrono>
#include <cstdint>
#include <stdexcept>

namespace base
{
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
		constexpr void AdjustSecondsIndexToOneMinute(int64_t &second_index)
		{
			if (second_index >= 0 && second_index < 60)
			{
				return;
			}

			AddMinutes(second_index / 60);
			second_index %= 60;
			if (second_index < 0)
			{
				AddMinutes(-1);
				second_index += 60;
			}
		}

		/* #endregion */

		/* #region 不考虑时区转换为本地时区的日期时间字符串 */

		base::String YearString() const
		{
			base::String ret{std::to_string(_year)};
			ret.PadLeft('0', base::StringLength{4});
			return ret;
		}

		base::String MonthString() const
		{
			base::String ret{std::to_string(_month)};
			ret.PadLeft('0', base::StringLength{2});
			return ret;
		}

		base::String DayString() const
		{
			base::String ret{std::to_string(_day)};
			ret.PadLeft('0', base::StringLength{2});
			return ret;
		}

		base::String HourString() const
		{
			base::String ret{std::to_string(_hour)};
			ret.PadLeft('0', base::StringLength{2});
			return ret;
		}

		base::String MinuteString() const
		{
			base::String ret{std::to_string(_minute)};
			ret.PadLeft('0', base::StringLength{2});
			return ret;
		}

		base::String SecondString() const
		{
			base::String ret{std::to_string(_second)};
			ret.PadLeft('0', base::StringLength{2});
			return ret;
		}

		base::String MillisecondString() const
		{
			base::String ret{std::to_string(_nanosecond / 1000 / 1000)};
			ret.PadLeft('0', base::StringLength{3});
			return ret;
		}

		base::String MicrosecondString() const
		{
			base::String ret{std::to_string(_nanosecond / 1000)};
			ret.PadLeft('0', base::StringLength{6});
			return ret;
		}

		base::String NanosecondString() const
		{
			base::String ret{std::to_string(_nanosecond)};
			ret.PadLeft('0', base::StringLength{9});
			return ret;
		}

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
		constexpr DateTime(int64_t year, int64_t month, int64_t day,
						   int64_t hour, int64_t minute, int64_t second,
						   int64_t nanosecond)
		{
			_year = year;
			_month = month;
			_day = day;
			_hour = hour;
			_minute = minute;
			_second = second;
			_nanosecond = nanosecond;

			CheckMonth();
			CheckDay();
			CheckHour();
			CheckMinute();
			CheckSecond();
			CheckNanosecond();
		}

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
		constexpr DateTime(base::UtcHourOffset utc_hour_offset,
						   int64_t year, int64_t month, int64_t day,
						   int64_t hour, int64_t minute, int64_t second,
						   int64_t nanosecond)
			: DateTime(year, month, day, hour, minute, second, nanosecond)
		{
			_utc_hour_offset = utc_hour_offset.Value();

			// 调整回 UTC + 0 时间。
			// 因为本类的字段储存的始终是 UTC + 0 时间。
			AddHours(-_utc_hour_offset);
		}

		///
		/// @brief 通过时间点构造。
		///
		/// @param time_point 时间点。epoch 时间戳，与时区无关。
		///
		constexpr DateTime(base::TimePointSinceEpoch const &time_point)
		{
			base::DateTime start{EpochStart()};
			start.AddNanoseconds(static_cast<std::chrono::nanoseconds>(time_point).count());
			*this = start;
		}

		///
		/// @brief 通过时间点构造一个 UTC 偏移的日期时间。
		///
		/// @param utc_hour_offset 你所处的时区的 UTC 小时偏移量。
		/// @param time_point 时间点。epoch 时间戳，与时区无关。
		///
		constexpr DateTime(base::UtcHourOffset utc_hour_offset,
						   base::TimePointSinceEpoch const &time_point)
			: DateTime(time_point)
		{
			_utc_hour_offset = utc_hour_offset.Value();
		}

		/* #endregion */

		/* #region 日期时间属性 */

		///
		/// @brief 获取日期时间中的年。
		///
		/// @note 本属性始终是 UTC+0 的日期时间。
		///
		/// @return
		///
		constexpr int64_t Year() const
		{
			return _year;
		}

		///
		/// @brief 获取日期时间中的月。
		///
		/// @note 本属性始终是 UTC+0 的日期时间。
		///
		/// @return
		///
		constexpr int64_t Month() const
		{
			return _month;
		}

		///
		/// @brief 获取日期时间中的日。
		///
		/// @note 本属性始终是 UTC+0 的日期时间。
		///
		/// @return
		///
		constexpr int64_t Day() const
		{
			return _day;
		}

		///
		/// @brief 获取日期时间中的小时。
		///
		/// @return
		///
		constexpr int64_t Hour() const
		{
			return _hour;
		}

		///
		/// @brief 获取日期时间中的分钟。
		///
		/// @return
		///
		constexpr int64_t Minute() const
		{
			return _minute;
		}

		///
		/// @brief 获取日期时间中的秒。
		///
		/// @return
		///
		constexpr int64_t Second() const
		{
			return _second;
		}

		///
		/// @brief 获取日期时间中的纳秒。
		///
		/// @return
		///
		constexpr int64_t Nanosecond() const
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
		constexpr void AddDays(int64_t value)
		{
			if (value == 0)
			{
				return;
			}

			// 以本月 1 日为 0 索引，建立日的索引。
			int64_t day_index = _day - 1 + value;
			AdjustDayIndexToOneMonth(day_index);
			_day = day_index + 1;
		}

		///
		/// @brief 增加小时。
		///
		/// @param value
		///
		constexpr void AddHours(int64_t value)
		{
			_hour += value;
			AdjustHourIndexToOneDay(_hour);
		}

		///
		/// @brief 增加分钟。
		///
		/// @param value
		///
		constexpr void AddMinutes(int64_t value)
		{
			_minute += value;
			AdjustMinuteIndexToOneHour(_minute);
		}

		///
		/// @brief 增加秒。
		///
		/// @param value
		///
		constexpr void AddSeconds(int64_t value)
		{
			_second += value;
			AdjustSecondsIndexToOneMinute(_second);
		}

		///
		/// @brief 增加纳秒。
		///
		/// @param value
		///
		constexpr void AddNanoseconds(int64_t value)
		{
			std::chrono::nanoseconds total_ns{_nanosecond + value};
			std::chrono::seconds second_part = std::chrono::duration_cast<std::chrono::seconds>(total_ns);
			std::chrono::nanoseconds ns_part = total_ns - second_part;
			AddSeconds(second_part.count());
			_nanosecond = ns_part.count();
		}

		constexpr base::DateTime operator+(std::chrono::seconds const &value) const
		{
			base::DateTime ret{*this};
			ret += value;
			return ret;
		}

		constexpr base::DateTime &operator+=(std::chrono::seconds const &value)
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
		constexpr base::TimePointSinceEpoch TimePointSinceEpoch() const
		{
			std::chrono::nanoseconds total_ns{};
			base::DateTime start{EpochStart()};

			// 把 start 的年份调整到当前年份，累加经过的纳秒数。
			while (true)
			{
				if (start._year == _year)
				{
					break;
				}
				else if (start._year > _year)
				{
					start._year--;
					total_ns -= std::chrono::days{start.CurrentYearDayCount()};
				}
				else if (start._year < _year)
				{
					total_ns += std::chrono::days{start.CurrentYearDayCount()};
					start._year++;
				}
			}

			// 因为 start 是 1 月，所以一定满足 start._month <= _month
			while (start._month < _month)
			{
				total_ns += std::chrono::days{start.CurrentMonthDayCount()};
				start._month++;
			}

			// 因为 start 是 1 日，所以 _day - start._day >= 0
			total_ns += std::chrono::days{_day - start._day};
			total_ns += std::chrono::hours{_hour - 0};
			total_ns += std::chrono::minutes{_minute - 0};
			total_ns += std::chrono::seconds{_second - 0};
			total_ns += std::chrono::nanoseconds{_nanosecond - 0};
			return base::TimePointSinceEpoch{total_ns};
		}

		///
		/// @brief 获取日期时间字符串构建器。
		///
		/// @note 不考虑时区。
		///
		/// @return
		///
		base::DateTimeStringBuilder DateTimeStringBuilder() const
		{
			return base::DateTimeStringBuilder{
				YearString().StdString(),
				MonthString().StdString(),
				DayString().StdString(),
				HourString().StdString(),
				MinuteString().StdString(),
				SecondString().StdString(),
				MillisecondString().StdString(),
				MicrosecondString().StdString(),
				NanosecondString().StdString(),
			};
		}

		///
		/// @brief 获取本地日期时间字符串构建器。
		///
		/// @note 考虑时区。
		///
		/// @return
		///
		base::DateTimeStringBuilder LocalDateTimeStringBuilder() const
		{
			DateTime copy{*this};
			copy.AddHours(_utc_hour_offset);
			return copy.DateTimeStringBuilder();
		}

		/* #region 比较 */

		constexpr bool operator==(DateTime const &another) const
		{
			std::array<int64_t, 7> date_time_array{
				_year,
				_month,
				_day,
				_hour,
				_minute,
				_second,
				_nanosecond,
			};

			std::array<int64_t, 7> another_date_time_array{
				another._year,
				another._month,
				another._day,
				another._hour,
				another._minute,
				another._second,
				another._nanosecond,
			};

			// 利用 std::array 的字典序比较。
			return date_time_array == another_date_time_array;
		}

		constexpr bool operator<(DateTime const &another) const
		{
			std::array<int64_t, 7> date_time_array{
				_year,
				_month,
				_day,
				_hour,
				_minute,
				_second,
				_nanosecond,
			};

			std::array<int64_t, 7> another_date_time_array{
				another._year,
				another._month,
				another._day,
				another._hour,
				another._minute,
				another._second,
				another._nanosecond,
			};

			// 利用 std::array 的字典序比较。
			return date_time_array < another_date_time_array;
		}

		constexpr bool operator>(DateTime const &another) const
		{
			std::array<int64_t, 7> date_time_array{
				_year,
				_month,
				_day,
				_hour,
				_minute,
				_second,
				_nanosecond,
			};

			std::array<int64_t, 7> another_date_time_array{
				another._year,
				another._month,
				another._day,
				another._hour,
				another._minute,
				another._second,
				another._nanosecond,
			};

			// 利用 std::array 的字典序比较。
			return date_time_array > another_date_time_array;
		}

		constexpr bool operator<=(DateTime const &another) const
		{
			std::array<int64_t, 7> date_time_array{
				_year,
				_month,
				_day,
				_hour,
				_minute,
				_second,
				_nanosecond,
			};

			std::array<int64_t, 7> another_date_time_array{
				another._year,
				another._month,
				another._day,
				another._hour,
				another._minute,
				another._second,
				another._nanosecond,
			};

			// 利用 std::array 的字典序比较。
			return date_time_array <= another_date_time_array;
		}

		constexpr bool operator>=(DateTime const &another) const
		{
			std::array<int64_t, 7> date_time_array{
				_year,
				_month,
				_day,
				_hour,
				_minute,
				_second,
				_nanosecond,
			};

			std::array<int64_t, 7> another_date_time_array{
				another._year,
				another._month,
				another._day,
				another._hour,
				another._minute,
				another._second,
				another._nanosecond,
			};

			// 利用 std::array 的字典序比较。
			return date_time_array >= another_date_time_array;
		}

		/* #endregion */

		///
		/// @brief 本日期时间的 UTC 偏移量。
		///
		/// @return
		///
		constexpr base::UtcHourOffset UtcHourOffset() const
		{
			return base::UtcHourOffset{_utc_hour_offset};
		}

		///
		/// @brief 本日期时间的 UTC 偏移量。
		///
		/// @note 设置本属性并不会影响内部的实际日期时间，仅仅是改变你打印输出。
		///
		/// @note 本类对象储存的始终是 UTC+0 的时间，设置 UTC 偏移量仅仅是影响
		/// LocalDateTimeStringBuilder 而已。也就是仅仅影响你想要按照你本地
		/// 时区得到日期时间字符串时的结果。
		///
		/// @param value
		///
		constexpr void SetUtcHourOffset(base::UtcHourOffset value)
		{
			_utc_hour_offset = value.Value();
		}

		///
		/// @brief 日期时间的字典序。
		///
		/// @return
		///
		constexpr int64_t DictionaryOrder() const
		{
			constexpr int64_t ns_coefficient = 1;
			constexpr int64_t us_coefficient = 1000 * ns_coefficient;
			constexpr int64_t ms_coefficient = 1000 * us_coefficient;
			constexpr int64_t seconds_coefficient = 1000 * ms_coefficient;
			constexpr int64_t minutes_coefficient = 60 * seconds_coefficient;
			constexpr int64_t hours_coefficient = 60 * minutes_coefficient;
			constexpr int64_t days_coefficient = 24 * hours_coefficient;
			constexpr int64_t months_coefficient = 31 * days_coefficient;
			constexpr int64_t years_coefficient = 12 * months_coefficient;

			int64_t order = _year * years_coefficient +
							_month * months_coefficient +
							_day * days_coefficient +
							_hour * hours_coefficient +
							_minute * minutes_coefficient +
							_second * seconds_coefficient +
							_nanosecond * ns_coefficient;

			return order;
		}

		///
		/// @brief epoch 起点日期。
		///
		/// @return
		///
		constexpr static base::DateTime EpochStart()
		{
			base::DateTime start{1970, 1, 1, 0, 0, 0, 0};
			return start;
		}
	};

} // namespace base

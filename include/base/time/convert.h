#pragma once
#include "base/time/DateTime.h"
#include "base/time/DateTimeStringBuilder.h"
#include "base/time/TimePointSinceEpoch.h"
#include "base/time/TimeSpan.h"
#include "base/time/UtcHourOffset.h"
#include <chrono>
#include <filesystem>
#include <string>
#include <type_traits>

namespace base
{
	/* #region 将 base::TimePointSinceEpoch 转换为 std::chrono::time_point */

	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::ms_time_point>)
	constexpr ReturnType Convert(base::TimePointSinceEpoch const &value)
	{
		return ms_time_point{static_cast<std::chrono::milliseconds>(value)};
	}

	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::s_time_point>)
	constexpr ReturnType Convert(base::TimePointSinceEpoch const &value)
	{
		return s_time_point{static_cast<std::chrono::seconds>(value)};
	}

	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::file_clock_time_point>)
	constexpr ReturnType Convert(base::TimePointSinceEpoch const &value)
	{
		// 文件时钟不准，并不是当前的 epoch 时间，而是与 epoch 时间之间有一个固定的偏移量。
		// 获取这个偏移量，然后将 _time_since_epoch 减去这个偏移量就得到了对应的文件时钟时间戳。
		auto offset = std::chrono::system_clock::now().time_since_epoch() -
					  std::filesystem::file_time_type::clock::now().time_since_epoch();

		return file_clock_time_point{static_cast<std::chrono::nanoseconds>(value) - offset};
	}

	/* #endregion */

	/* #region 将 base::TimePointSinceEpoch 转换为 std::chrono::zoned_time */

	///
	/// @brief 将 value 转换为 UTC + 0 区域时间。
	///
	/// @param value
	///
	/// @return
	///
	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::ns_zoned_time>)
	constexpr ReturnType Convert(base::TimePointSinceEpoch const &value)
	{
		auto time_point = static_cast<base::ns_time_point>(value);
		return ns_zoned_time{"UTC", time_point};
	}

	///
	/// @brief 将 value 转换为 UTC + offset 区域时间。
	///
	/// @param offset 你所在的区域的时间相对于 UTC 的偏移量。
	/// @param value 被转换的时间点。
	///
	/// @return
	///
	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::ns_zoned_time>)
	constexpr ReturnType Convert(base::UtcHourOffset const &offset,
								 base::TimePointSinceEpoch const &value)
	{
		base::TimePointSinceEpoch utc8 = value;
		utc8 += offset.Value() * base::TimeSpan{std::chrono::seconds{60 * 60}};
		return Convert<base::ns_zoned_time>(utc8);
	}

	///
	/// @brief 将 value 转换为 UTC + 0 区域时间。
	///
	/// @param value
	///
	/// @return
	///
	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::us_zoned_time>)
	constexpr ReturnType Convert(base::TimePointSinceEpoch const &value)
	{
		auto time_point = static_cast<base::us_time_point>(value);
		return us_zoned_time{"UTC", time_point};
	}

	///
	/// @brief 将 value 转换为 UTC + offset 区域时间。
	///
	/// @param offset 你所在的区域的时间相对于 UTC 的偏移量。
	/// @param value 被转换的时间点。
	///
	/// @return
	///
	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::us_zoned_time>)
	constexpr ReturnType Convert(base::UtcHourOffset const &offset,
								 base::TimePointSinceEpoch const &value)
	{
		base::TimePointSinceEpoch utc8 = value;
		utc8 += offset.Value() * base::TimeSpan{std::chrono::seconds{60 * 60}};
		return Convert<base::us_zoned_time>(utc8);
	}

	///
	/// @brief 将 value 转换为 UTC + 0 区域时间。
	///
	/// @param value
	///
	/// @return
	///
	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::ms_zoned_time>)
	constexpr ReturnType Convert(base::TimePointSinceEpoch const &value)
	{
		auto time_point = Convert<base::ms_time_point>(value);
		return ms_zoned_time{"UTC", time_point};
	}

	///
	/// @brief 将 value 转换为 UTC + offset 区域时间。
	///
	/// @param offset 你所在的区域的时间相对于 UTC 的偏移量。
	/// @param value 被转换的时间点。
	///
	/// @return
	///
	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::ms_zoned_time>)
	constexpr ReturnType Convert(base::UtcHourOffset const &offset,
								 base::TimePointSinceEpoch const &value)
	{
		base::TimePointSinceEpoch utc8 = value;
		utc8 += offset.Value() * base::TimeSpan{std::chrono::seconds{60 * 60}};
		return Convert<base::ms_zoned_time>(utc8);
	}

	///
	/// @brief 将 value 转换为 UTC + 0 区域时间。
	///
	/// @param value
	///
	/// @return
	///
	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::s_zoned_time>)
	constexpr ReturnType Convert(base::TimePointSinceEpoch const &value)
	{
		auto time_point = Convert<base::s_time_point>(value);
		return s_zoned_time{"UTC", time_point};
	}

	///
	/// @brief 将 value 转换为 UTC + offset 区域时间。
	///
	/// @param offset 你所在的区域的时间相对于 UTC 的偏移量。
	/// @param value 被转换的时间点。
	///
	/// @return
	///
	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::s_zoned_time>)
	constexpr ReturnType Convert(base::UtcHourOffset const &offset,
								 base::TimePointSinceEpoch const &value)
	{
		base::TimePointSinceEpoch utc8 = value;
		utc8 += offset.Value() * base::TimeSpan{std::chrono::seconds{60 * 60}};
		return Convert<base::s_zoned_time>(utc8);
	}

	/* #endregion */

	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, std::chrono::year_month_day>)
	constexpr ReturnType Convert(base::TimePointSinceEpoch const &value)
	{
		std::chrono::year_month_day ret = static_cast<std::chrono::year_month_day>(value);
		return ret;
	}

	/* #region 将 base::TimePointSinceEpoch 转换为字符串。 */

	///
	/// @brief 将时刻转换为字符串。
	///
	/// @param value 时刻。
	///
	/// @return
	///
	inline std::string to_string(base::TimePointSinceEpoch const &value)
	{
		base::DateTime date_time{
			base::UtcHourOffset{8},
			value,
		};

		base::DateTimeStringBuilder date_time_string_builder = date_time.LocalDateTimeStringBuilder();
		date_time_string_builder.SetYearMonthDaySeparator('/');

		return date_time_string_builder.ToString();
	}

	///
	/// @brief 将时刻转换为字符串。
	///
	/// @param value 时刻。
	/// @param utc_hour_offset 要转换为的日期时间的时区。
	///
	/// @return
	///
	inline std::string to_string(base::TimePointSinceEpoch const &value,
								 base::UtcHourOffset const &utc_hour_offset)
	{
		base::DateTime date_time{
			utc_hour_offset,
			value,
		};

		base::DateTimeStringBuilder date_time_string_builder = date_time.LocalDateTimeStringBuilder();
		date_time_string_builder.SetYearMonthDaySeparator('/');

		return date_time_string_builder.ToString();
	}

	/* #endregion */

	/* #region std::chrono::zoned_time 转换为字符串 */

	inline std::string to_string(base::ns_zoned_time const &value)
	{
		return std::format("{:%Y-%m-%d %H:%M:%S}", value);
	}

	inline std::string to_string(base::us_zoned_time const &value)
	{
		return std::format("{:%Y-%m-%d %H:%M:%S}", value);
	}

	inline std::string to_string(base::ms_zoned_time const &value)
	{
		return std::format("{:%Y-%m-%d %H:%M:%S}", value);
	}

	inline std::string to_string(base::s_zoned_time const &value)
	{
		return std::format("{:%Y-%m-%d %H:%M:%S}", value);
	}

	/* #endregion */

} // namespace base

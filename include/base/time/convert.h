#pragma once
#include "base/time/TimePointSinceEpoch.h"
#include "base/time/TimeSpan.h"
#include "base/time/UtcHourOffset.h"
#include <chrono>
#include <filesystem>
#include <string>
#include <type_traits>

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

#if HAS_THREAD

	/* #region 转换为 base::TimePointSinceEpoch */
	base::TimePointSinceEpoch ToTimePointSinceEpoch(ns_time_point const &value);
	base::TimePointSinceEpoch ToTimePointSinceEpoch(us_time_point const &value);
	base::TimePointSinceEpoch ToTimePointSinceEpoch(ms_time_point const &value);
	base::TimePointSinceEpoch ToTimePointSinceEpoch(s_time_point const &value);
	base::TimePointSinceEpoch ToTimePointSinceEpoch(file_clock_time_point const &value);

	/* #endregion */

	/* #region 转换为 std::chrono::time_point */

	template <typename ReturnType>
		requires(std::is_same_v<ReturnType, base::ns_time_point>)
	constexpr ReturnType Convert(base::TimePointSinceEpoch const &value)
	{
		return ns_time_point{static_cast<std::chrono::nanoseconds>(value)};
	}

	base::us_time_point to_us_time_point(base::TimePointSinceEpoch const &value);
	base::ms_time_point to_ms_time_point(base::TimePointSinceEpoch const &value);
	base::s_time_point to_s_time_point(base::TimePointSinceEpoch const &value);
	base::file_clock_time_point to_file_clock_time_point(base::TimePointSinceEpoch const &value);

	/* #endregion */

	/* #region 转换为 std::chrono::zoned_time */

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
		auto time_point = Convert<base::ns_time_point>(value);
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
		auto time_point = base::to_us_time_point(value);
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
		auto time_point = base::to_ms_time_point(value);
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
		auto time_point = base::to_s_time_point(value);
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
		std::chrono::year_month_day ret{static_cast<std::chrono::local_days>(value)};
		return ret;
	}

	std::string to_string(base::TimePointSinceEpoch const &value);
	std::string to_string(base::ns_zoned_time const &value);
	std::string to_string(base::us_zoned_time const &value);
	std::string to_string(base::ms_zoned_time const &value);
	std::string to_string(base::s_zoned_time const &value);

#endif // HAS_THREAD

} // namespace base

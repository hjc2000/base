#pragma once
#include "base/time/UtcHourOffset.h"
#include <chrono>
#include <filesystem>

namespace base
{
	using local_days_duration_type = decltype(std::chrono::local_days{}.time_since_epoch());

	using ns_time_point = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;
	using us_time_point = std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds>;
	using ms_time_point = std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>;
	using s_time_point = std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>;
	using file_clock_time_point = decltype(std::filesystem::directory_entry{}.last_write_time());

	using ns_zoned_time = std::chrono::zoned_time<std::chrono::nanoseconds>;
	using us_zoned_time = std::chrono::zoned_time<std::chrono::microseconds>;
	using ms_zoned_time = std::chrono::zoned_time<std::chrono::milliseconds>;
	using s_zoned_time = std::chrono::zoned_time<std::chrono::seconds>;

	class TimePointSinceEpoch;

	base::TimePointSinceEpoch ToTimePointSinceEpoch(ns_time_point const &value);

	/* #region 转换为区域时间 */

#if HAS_THREAD

	///
	/// @brief 将 value 转换为 UTC + 0 区域时间。
	///
	/// @param value
	///
	/// @return base::ns_zoned_time
	///
	base::ns_zoned_time to_ns_zoned_time(base::TimePointSinceEpoch const &value);

	///
	/// @brief 将 value 转换为 UTC + offset 区域时间。
	///
	/// @param offset 你所在的区域的时间相对于 UTC 的偏移量。
	/// @param value 被转换的时间点。
	///
	/// @return base::ns_zoned_time
	///
	base::ns_zoned_time to_ns_zoned_time(base::UtcHourOffset const &offset,
										 base::TimePointSinceEpoch const &value);

	///
	/// @brief 将 value 转换为 UTC + 0 区域时间。
	///
	/// @param value
	///
	/// @return base::us_zoned_time
	///
	base::us_zoned_time to_us_zoned_time(base::TimePointSinceEpoch const &value);

	///
	/// @brief 将 value 转换为 UTC + offset 区域时间。
	///
	/// @param offset 你所在的区域的时间相对于 UTC 的偏移量。
	/// @param value 被转换的时间点。
	///
	/// @return base::us_zoned_time
	///
	base::us_zoned_time to_us_zoned_time(base::UtcHourOffset const &offset,
										 base::TimePointSinceEpoch const &value);

	///
	/// @brief 将 value 转换为 UTC + 0 区域时间。
	///
	/// @param value
	///
	/// @return base::ms_zoned_time
	///
	base::ms_zoned_time to_ms_zoned_time(base::TimePointSinceEpoch const &value);

	///
	/// @brief 将 value 转换为 UTC + offset 区域时间。
	///
	/// @param offset 你所在的区域的时间相对于 UTC 的偏移量。
	/// @param value 被转换的时间点。
	///
	/// @return base::ms_zoned_time
	///
	base::ms_zoned_time to_ms_zoned_time(base::UtcHourOffset const &offset,
										 base::TimePointSinceEpoch const &value);

	///
	/// @brief 将 value 转换为 UTC + 0 区域时间。
	///
	/// @param value
	///
	/// @return base::s_zoned_time
	///
	base::s_zoned_time to_s_zoned_time(base::TimePointSinceEpoch const &value);

	///
	/// @brief 将 value 转换为 UTC + offset 区域时间。
	///
	/// @param offset 你所在的区域的时间相对于 UTC 的偏移量。
	/// @param value 被转换的时间点。
	///
	/// @return base::s_zoned_time
	///
	base::s_zoned_time to_s_zoned_time(base::UtcHourOffset const &offset,
									   base::TimePointSinceEpoch const &value);

#endif // HAS_THREAD
	/* #endregion */

} // namespace base

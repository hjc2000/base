#include "converte.h"
#include "base/time/TimePointSinceEpoch.h"
#include <chrono>

base::TimePointSinceEpoch base::ToTimePointSinceEpoch(ns_time_point const &value)
{
	return base::TimePointSinceEpoch{value.time_since_epoch()};
}

base::TimePointSinceEpoch base::ToTimePointSinceEpoch(us_time_point const &value)
{
	return base::TimePointSinceEpoch{value.time_since_epoch()};
}

base::TimePointSinceEpoch base::ToTimePointSinceEpoch(ms_time_point const &value)
{
	return base::TimePointSinceEpoch{value.time_since_epoch()};
}

base::TimePointSinceEpoch base::ToTimePointSinceEpoch(s_time_point const &value)
{
	return base::TimePointSinceEpoch{value.time_since_epoch()};
}

base::TimePointSinceEpoch base::ToTimePointSinceEpoch(file_clock_time_point const &value)
{
	std::chrono::nanoseconds time_since_epoch = value.time_since_epoch();

	// 文件时钟不准，并不是当前的 epoch 时间，而是与 epoch 时间之间有一个固定的偏移量。
	// 获取这个偏移量，然后将文件时钟的时间戳加上偏移量就得到了文件时钟时间戳对应的 epoch 时间戳。
	auto delta = std::chrono::system_clock::now().time_since_epoch() -
				 std::filesystem::file_time_type::clock::now().time_since_epoch();

	time_since_epoch += delta;
	return base::TimePointSinceEpoch{time_since_epoch};
}

/* #region 转换为区域时间 */

#if HAS_THREAD

base::ns_zoned_time base::to_ns_zoned_time(base::TimePointSinceEpoch const &value)
{
	auto time_point = static_cast<ns_time_point>(value);
	return ns_zoned_time{"UTC", time_point};
}

base::ns_zoned_time base::to_ns_zoned_time(base::UtcHourOffset const &offset,
										   base::TimePointSinceEpoch const &value)
{
	base::TimePointSinceEpoch utc8 = value;
	utc8 += offset.Value() * base::TimeSpan{std::chrono::seconds{60 * 60}};
	return to_ns_zoned_time(utc8);
}

base::us_zoned_time base::to_us_zoned_time(base::TimePointSinceEpoch const &value)
{
	auto time_point = static_cast<us_time_point>(value);
	return us_zoned_time{"UTC", time_point};
}

base::us_zoned_time base::to_us_zoned_time(base::UtcHourOffset const &offset,
										   base::TimePointSinceEpoch const &value)
{
	base::TimePointSinceEpoch utc8 = value;
	utc8 += offset.Value() * base::TimeSpan{std::chrono::seconds{60 * 60}};
	return to_us_zoned_time(utc8);
}

base::ms_zoned_time base::to_ms_zoned_time(base::TimePointSinceEpoch const &value)
{
	auto time_point = static_cast<ms_time_point>(value);
	return ms_zoned_time{"UTC", time_point};
}

base::ms_zoned_time base::to_ms_zoned_time(base::UtcHourOffset const &offset,
										   base::TimePointSinceEpoch const &value)
{
	base::TimePointSinceEpoch utc8 = value;
	utc8 += offset.Value() * base::TimeSpan{std::chrono::seconds{60 * 60}};
	return to_ms_zoned_time(utc8);
}

base::s_zoned_time base::to_s_zoned_time(base::TimePointSinceEpoch const &value)
{
	auto time_point = static_cast<s_time_point>(value);
	return s_zoned_time{"UTC", time_point};
}

base::s_zoned_time base::to_s_zoned_time(base::UtcHourOffset const &offset,
										 base::TimePointSinceEpoch const &value)
{
	base::TimePointSinceEpoch utc8 = value;
	utc8 += offset.Value() * base::TimeSpan{std::chrono::seconds{60 * 60}};
	return to_s_zoned_time(utc8);
}

#endif // HAS_THREAD

/* #endregion */

#include "converte.h"
#include "base/time/TimePointSinceEpoch.h"

base::TimePointSinceEpoch base::ToTimePointSinceEpoch(ns_time_point const &value)
{
	return base::TimePointSinceEpoch{value.time_since_epoch()};
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

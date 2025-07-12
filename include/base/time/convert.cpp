#include "convert.h"
#include "base/time/TimePointSinceEpoch.h"
#include <chrono>

#if HAS_THREAD

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

/* #region 转换为 std::chrono::time_point */

base::ms_time_point base::to_ms_time_point(base::TimePointSinceEpoch const &value)
{
	return ms_time_point{static_cast<std::chrono::milliseconds>(value)};
}

base::s_time_point base::to_s_time_point(base::TimePointSinceEpoch const &value)
{
	return s_time_point{static_cast<std::chrono::seconds>(value)};
}

base::file_clock_time_point base::to_file_clock_time_point(base::TimePointSinceEpoch const &value)
{
	// 文件时钟不准，并不是当前的 epoch 时间，而是与 epoch 时间之间有一个固定的偏移量。
	// 获取这个偏移量，然后将 _time_since_epoch 减去这个偏移量就得到了对应的文件时钟时间戳。
	auto delta = std::chrono::system_clock::now().time_since_epoch() -
				 std::filesystem::file_time_type::clock::now().time_since_epoch();

	return file_clock_time_point{static_cast<std::chrono::nanoseconds>(value) - delta};
}

/* #endregion */

#endif // HAS_THREAD

#if HAS_THREAD

std::string base::to_string(base::TimePointSinceEpoch const &value)
{
	return base::to_string(base::Convert<base::ns_zoned_time>(base::UtcHourOffset{8}, value));
}

std::string base::to_string(base::ns_zoned_time const &value)
{
	return std::format("{:%Y-%m-%d %H:%M:%S}", value);
}

std::string base::to_string(base::us_zoned_time const &value)
{
	return std::format("{:%Y-%m-%d %H:%M:%S}", value);
}

std::string base::to_string(base::ms_zoned_time const &value)
{
	return std::format("{:%Y-%m-%d %H:%M:%S}", value);
}

std::string base::to_string(base::s_zoned_time const &value)
{
	return std::format("{:%Y-%m-%d %H:%M:%S}", value);
}

#endif // HAS_THREAD

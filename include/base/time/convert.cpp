#include "convert.h"

#if HAS_THREAD

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

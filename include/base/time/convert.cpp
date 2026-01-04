#include "convert.h" // IWYU pragma: keep

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

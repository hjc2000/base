#include "TimePointSinceEpoch.h"

#if HAS_THREAD
#include <format>
#endif

#pragma region 构造函数

base::TimePointSinceEpoch::TimePointSinceEpoch()
{
}

base::TimePointSinceEpoch::TimePointSinceEpoch(std::chrono::nanoseconds const &value)
{
	_time_since_epoch = value;
}

base::TimePointSinceEpoch::TimePointSinceEpoch(std::chrono::microseconds const &value)
{
	_time_since_epoch = std::chrono::nanoseconds{value};
}

base::TimePointSinceEpoch::TimePointSinceEpoch(std::chrono::milliseconds const &value)
{
	_time_since_epoch = std::chrono::nanoseconds{value};
}

base::TimePointSinceEpoch::TimePointSinceEpoch(std::chrono::seconds const &value)
{
	_time_since_epoch = std::chrono::nanoseconds{value};
}

base::TimePointSinceEpoch::TimePointSinceEpoch(timespec const &value)
{
	_time_since_epoch = std::chrono::seconds{value.tv_sec} + std::chrono::nanoseconds{value.tv_nsec};
}

#pragma endregion

#pragma region HAS_THREAD 限定构造函数
#if HAS_THREAD

base::TimePointSinceEpoch::TimePointSinceEpoch(std::chrono::time_point<std::chrono::system_clock,
																	   std::chrono::nanoseconds> const &value)
{
	_time_since_epoch = value.time_since_epoch();
}

base::TimePointSinceEpoch::TimePointSinceEpoch(std::chrono::time_point<std::chrono::system_clock,
																	   std::chrono::microseconds> const &value)
{
	_time_since_epoch = value.time_since_epoch();
}

base::TimePointSinceEpoch::TimePointSinceEpoch(std::chrono::time_point<std::chrono::system_clock,
																	   std::chrono::milliseconds> const &value)
{
	_time_since_epoch = value.time_since_epoch();
}

base::TimePointSinceEpoch::TimePointSinceEpoch(std::chrono::time_point<std::chrono::system_clock,
																	   std::chrono::seconds> const &value)
{
	_time_since_epoch = value.time_since_epoch();
}

#endif
#pragma endregion

#pragma region 数据转换

base::TimePointSinceEpoch::operator std::chrono::nanoseconds() const
{
	return _time_since_epoch;
}

base::TimePointSinceEpoch::operator std::chrono::microseconds() const
{
	return std::chrono::duration_cast<std::chrono::microseconds>(_time_since_epoch);
}

base::TimePointSinceEpoch::operator std::chrono::milliseconds() const
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(_time_since_epoch);
}

base::TimePointSinceEpoch::operator std::chrono::seconds() const
{
	return std::chrono::duration_cast<std::chrono::seconds>(_time_since_epoch);
}

base::TimePointSinceEpoch::operator timespec() const
{
	timespec ts{};
	std::chrono::seconds seconds_part = std::chrono::duration_cast<std::chrono::seconds>(_time_since_epoch);
	std::chrono::nanoseconds nanoseconds_part = _time_since_epoch - std::chrono::nanoseconds{seconds_part};

	// 整秒部分
	ts.tv_sec = static_cast<decltype(ts.tv_sec)>(seconds_part.count());

	// 纳秒部分
	ts.tv_nsec = static_cast<decltype(ts.tv_nsec)>(nanoseconds_part.count());
	return ts;
}

#pragma endregion

#pragma region HAS_THREAD 限定数据转换
#if HAS_THREAD

base::TimePointSinceEpoch::operator std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>() const
{
	return std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>{
		static_cast<std::chrono::nanoseconds>(*this),
	};
}

base::TimePointSinceEpoch::operator std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds>() const
{
	return std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds>{
		static_cast<std::chrono::microseconds>(*this),
	};
}

base::TimePointSinceEpoch::operator std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>() const
{
	return std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>{
		static_cast<std::chrono::milliseconds>(*this),
	};
}

base::TimePointSinceEpoch::operator std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>() const
{
	return std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>{
		static_cast<std::chrono::seconds>(*this),
	};
}

base::TimePointSinceEpoch::operator std::chrono::zoned_time<std::chrono::nanoseconds>() const
{
	return ToNanosecondsZonedTime();
}

base::TimePointSinceEpoch::operator std::chrono::zoned_time<std::chrono::microseconds>() const
{
	return ToMicrosecondsZonedTime();
}

base::TimePointSinceEpoch::operator std::chrono::zoned_time<std::chrono::milliseconds>() const
{
	return ToMillisecondsZonedTime();
}

base::TimePointSinceEpoch::operator std::chrono::zoned_time<std::chrono::seconds>() const
{
	return ToSecondsZonedTime();
}

std::chrono::zoned_time<std::chrono::nanoseconds> base::TimePointSinceEpoch::ToNanosecondsZonedTime() const
{
	return std::chrono::zoned_time<std::chrono::nanoseconds>{
		"UTC",
		static_cast<std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>>(*this),
	};
}

std::chrono::zoned_time<std::chrono::microseconds> base::TimePointSinceEpoch::ToMicrosecondsZonedTime() const
{
	return std::chrono::zoned_time<std::chrono::microseconds>{
		"UTC",
		static_cast<std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds>>(*this),
	};
}

std::chrono::zoned_time<std::chrono::milliseconds> base::TimePointSinceEpoch::ToMillisecondsZonedTime() const
{
	return std::chrono::zoned_time<std::chrono::milliseconds>{
		"UTC",
		static_cast<std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>>(*this),
	};
}

std::chrono::zoned_time<std::chrono::seconds> base::TimePointSinceEpoch::ToSecondsZonedTime() const
{
	return std::chrono::zoned_time<std::chrono::seconds>{
		"UTC",
		static_cast<std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>>(*this),
	};
}

std::string base::TimePointSinceEpoch::NanosecondsZonedTimeString() const
{
	return std::format("{:%Y-%m-%d %H:%M:%S}", ToNanosecondsZonedTime());
}

std::string base::TimePointSinceEpoch::MicrosecondsZonedTimeString() const
{
	return std::format("{:%Y-%m-%d %H:%M:%S}", ToMicrosecondsZonedTime());
}

std::string base::TimePointSinceEpoch::MillisecondsZonedTimeString() const
{
	return std::format("{:%Y-%m-%d %H:%M:%S}", ToMillisecondsZonedTime());
}

std::string base::TimePointSinceEpoch::SecondsZonedTimeString() const
{
	return std::format("{:%Y-%m-%d %H:%M:%S}", ToSecondsZonedTime());
}

#endif
#pragma endregion

#pragma region 加减运算符

base::TimeSpan base::TimePointSinceEpoch::operator-(base::TimePointSinceEpoch const &rhs) const
{
	return base::TimeSpan{_time_since_epoch - rhs._time_since_epoch};
}

base::TimePointSinceEpoch base::TimePointSinceEpoch::operator+(base::TimeSpan const &rhs) const
{
	return base::TimePointSinceEpoch{_time_since_epoch + static_cast<std::chrono::nanoseconds>(rhs)};
}

base::TimePointSinceEpoch base::TimePointSinceEpoch::operator-(base::TimeSpan const &rhs) const
{
	return base::TimePointSinceEpoch{_time_since_epoch - static_cast<std::chrono::nanoseconds>(rhs)};
}

#pragma endregion

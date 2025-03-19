#include "TimePointSinceEpoch.h"
#include <chrono>
#include <cstdint>

/* #region 构造函数 */

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

#if HAS_THREAD
/* #region 从时间点构造 */

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

base::TimePointSinceEpoch::TimePointSinceEpoch(file_clock_time_point const &value)
{
	_time_since_epoch = value.time_since_epoch();

	auto delta = std::chrono::system_clock::now().time_since_epoch() -
				 std::filesystem::file_time_type::clock::now().time_since_epoch();

	_time_since_epoch += delta;
}

/* #endregion */
#endif

/* #endregion */

/* #region 强制转换 */

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

#if HAS_THREAD
/* #region 转换为时间点 */

base::TimePointSinceEpoch::operator ns_time_point() const
{
	return ns_time_point{static_cast<std::chrono::nanoseconds>(*this)};
}

base::TimePointSinceEpoch::operator us_time_point() const
{
	return us_time_point{static_cast<std::chrono::microseconds>(*this)};
}

base::TimePointSinceEpoch::operator ms_time_point() const
{
	return ms_time_point{static_cast<std::chrono::milliseconds>(*this)};
}

base::TimePointSinceEpoch::operator s_time_point() const
{
	return s_time_point{static_cast<std::chrono::seconds>(*this)};
}

base::TimePointSinceEpoch::operator file_clock_time_point() const
{
	auto delta = std::chrono::system_clock::now().time_since_epoch() -
				 std::filesystem::file_time_type::clock::now().time_since_epoch();

	return file_clock_time_point{_time_since_epoch - delta};
}

/* #endregion */

/* #region 转换为 zoned_time */

base::TimePointSinceEpoch::operator std::chrono::zoned_time<std::chrono::nanoseconds>() const
{
	base::TimePointSinceEpoch utc8 = *this + 8 * base::TimeSpan{std::chrono::seconds{60 * 60}};
	auto time_point = static_cast<ns_time_point>(utc8);
	return std::chrono::zoned_time<std::chrono::nanoseconds>{"UTC", time_point};
}

base::TimePointSinceEpoch::operator std::chrono::zoned_time<std::chrono::microseconds>() const
{
	base::TimePointSinceEpoch utc8 = *this + 8 * base::TimeSpan{std::chrono::seconds{60 * 60}};
	auto time_point = static_cast<us_time_point>(utc8);
	return std::chrono::zoned_time<std::chrono::microseconds>{"UTC", time_point};
}

base::TimePointSinceEpoch::operator std::chrono::zoned_time<std::chrono::milliseconds>() const
{
	base::TimePointSinceEpoch utc8 = *this + 8 * base::TimeSpan{std::chrono::seconds{60 * 60}};
	auto time_point = static_cast<ms_time_point>(utc8);
	return std::chrono::zoned_time<std::chrono::milliseconds>{"UTC", time_point};
}

base::TimePointSinceEpoch::operator std::chrono::zoned_time<std::chrono::seconds>() const
{
	base::TimePointSinceEpoch utc8 = *this + 8 * base::TimeSpan{std::chrono::seconds{60 * 60}};
	auto time_point = static_cast<s_time_point>(utc8);
	return std::chrono::zoned_time<std::chrono::seconds>{"UTC", time_point};
}

/* #endregion */
#endif

/* #endregion */

/* #region 四则运算 */

base::TimeSpan base::TimePointSinceEpoch::operator-(base::TimePointSinceEpoch const &rhs) const
{
	return base::TimeSpan{_time_since_epoch - rhs._time_since_epoch};
}

base::TimePointSinceEpoch base::TimePointSinceEpoch::operator+(base::TimeSpan const &rhs) const
{
	return base::TimePointSinceEpoch{_time_since_epoch + static_cast<std::chrono::nanoseconds>(rhs)};
}

base::TimePointSinceEpoch &base::TimePointSinceEpoch::operator+=(base::TimeSpan const &rhs)
{
	_time_since_epoch += static_cast<std::chrono::nanoseconds>(rhs);
	return *this;
}

base::TimePointSinceEpoch base::TimePointSinceEpoch::operator-(base::TimeSpan const &rhs) const
{
	return base::TimePointSinceEpoch{_time_since_epoch - static_cast<std::chrono::nanoseconds>(rhs)};
}

base::TimePointSinceEpoch &base::TimePointSinceEpoch::operator-=(base::TimeSpan const &rhs)
{
	_time_since_epoch -= static_cast<std::chrono::nanoseconds>(rhs);
	return *this;
}

base::TimePointSinceEpoch base::TimePointSinceEpoch::operator*(int64_t value) const
{
	return base::TimePointSinceEpoch{std::chrono::nanoseconds{_time_since_epoch.count() * value}};
}

base::TimePointSinceEpoch &base::TimePointSinceEpoch::operator*=(int64_t value)
{
	_time_since_epoch = std::chrono::nanoseconds{_time_since_epoch.count() * value};
	return *this;
}

/* #endregion */

/* #region 比较 */

bool base::TimePointSinceEpoch::operator==(base::TimePointSinceEpoch const &another) const
{
	return _time_since_epoch == another._time_since_epoch;
}

bool base::TimePointSinceEpoch::operator<(base::TimePointSinceEpoch const &another) const
{
	return _time_since_epoch < another._time_since_epoch;
}

bool base::TimePointSinceEpoch::operator>(base::TimePointSinceEpoch const &another) const
{
	return _time_since_epoch > another._time_since_epoch;
}

bool base::TimePointSinceEpoch::operator<=(base::TimePointSinceEpoch const &another) const
{
	return _time_since_epoch <= another._time_since_epoch;
}

bool base::TimePointSinceEpoch::operator>=(base::TimePointSinceEpoch const &another) const
{
	return _time_since_epoch >= another._time_since_epoch;
}

/* #endregion */

/* #region 转换为字符串 */

#if HAS_THREAD
/* #region 转换为区域时间字符串 */

std::string base::TimePointSinceEpoch::NanosecondsZonedTimeString() const
{
	return std::format("{:%Y-%m-%d %H:%M:%S}", static_cast<std::chrono::zoned_time<std::chrono::nanoseconds>>(*this));
}

std::string base::TimePointSinceEpoch::MicrosecondsZonedTimeString() const
{
	return std::format("{:%Y-%m-%d %H:%M:%S}", static_cast<std::chrono::zoned_time<std::chrono::microseconds>>(*this));
}

std::string base::TimePointSinceEpoch::MillisecondsZonedTimeString() const
{
	return std::format("{:%Y-%m-%d %H:%M:%S}", static_cast<std::chrono::zoned_time<std::chrono::milliseconds>>(*this));
}

std::string base::TimePointSinceEpoch::SecondsZonedTimeString() const
{
	return std::format("{:%Y-%m-%d %H:%M:%S}", static_cast<std::chrono::zoned_time<std::chrono::seconds>>(*this));
}

/* #endregion */
#endif

std::string base::TimePointSinceEpoch::ToString() const
{
#if HAS_THREAD
	return NanosecondsZonedTimeString();
#else
	return std::to_string(_time_since_epoch.count()) + " ns";
#endif
}

/* #endregion */

base::TimePointSinceEpoch operator*(int64_t left, base::TimePointSinceEpoch const &right)
{
	return right * left;
}

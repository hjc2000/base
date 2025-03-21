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
	_time_since_epoch = std::chrono::seconds{value.tv_sec} +
						std::chrono::nanoseconds{value.tv_nsec};
}

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

base::TimePointSinceEpoch::operator std::chrono::local_days() const
{
	local_days_duration_type duration = std::chrono::duration_cast<local_days_duration_type>(_time_since_epoch);
	std::chrono::local_days ret{duration};
	return ret;
}

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

base::TimePointSinceEpoch operator*(int64_t left, base::TimePointSinceEpoch const &right)
{
	return right * left;
}

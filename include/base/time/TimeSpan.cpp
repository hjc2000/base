#include "TimeSpan.h"

#pragma region 构造函数

base::TimeSpan::TimeSpan()
{
}

base::TimeSpan::TimeSpan(std::chrono::nanoseconds const &value)
{
	_span = value;
}

base::TimeSpan::TimeSpan(std::chrono::microseconds const &value)
{
	_span = std::chrono::nanoseconds{value};
}

base::TimeSpan::TimeSpan(std::chrono::milliseconds const &value)
{
	_span = std::chrono::nanoseconds{value};
}

base::TimeSpan::TimeSpan(std::chrono::seconds const &value)
{
	_span = std::chrono::nanoseconds{value};
}

base::TimeSpan::TimeSpan(timespec const &value)
{
	_span = std::chrono::seconds{value.tv_sec} + std::chrono::nanoseconds{value.tv_nsec};
}

#pragma endregion

#pragma region 强制转换运算符

base::TimeSpan::operator std::chrono::nanoseconds() const
{
	return _span;
}

base::TimeSpan::operator std::chrono::microseconds() const
{
	return std::chrono::duration_cast<std::chrono::microseconds>(_span);
}

base::TimeSpan::operator std::chrono::milliseconds() const
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(_span);
}

base::TimeSpan::operator std::chrono::seconds() const
{
	return std::chrono::duration_cast<std::chrono::seconds>(_span);
}

base::TimeSpan::operator timespec() const
{
	timespec ts{};
	std::chrono::seconds seconds_part = std::chrono::duration_cast<std::chrono::seconds>(_span);
	std::chrono::nanoseconds nanoseconds_part = _span - std::chrono::nanoseconds{seconds_part};

	// 整秒部分
	ts.tv_sec = static_cast<decltype(ts.tv_sec)>(seconds_part.count());

	// 纳秒部分
	ts.tv_nsec = static_cast<decltype(ts.tv_nsec)>(nanoseconds_part.count());
	return ts;
}

#pragma endregion

#pragma region 四则运算符

base::TimeSpan base::TimeSpan::operator+(base::TimeSpan const &rhs) const
{
	return base::TimeSpan{_span + rhs._span};
}

base::TimeSpan &base::TimeSpan::operator+=(base::TimeSpan const &rhs)
{
	_span += rhs._span;
	return *this;
}

base::TimeSpan base::TimeSpan::operator-(base::TimeSpan const &rhs) const
{
	return base::TimeSpan{_span - rhs._span};
}

base::TimeSpan &base::TimeSpan::operator-=(base::TimeSpan const &rhs)
{
	_span -= rhs._span;
	return *this;
}

base::TimeSpan base::TimeSpan::operator*(int64_t value) const
{
	return base::TimeSpan{std::chrono::nanoseconds{_span.count() * value}};
}

base::TimeSpan &base::TimeSpan::operator*=(int64_t value)
{
	_span = std::chrono::nanoseconds{_span.count() * value};
	return *this;
}

#pragma endregion

base::TimeSpan operator*(int64_t left, base::TimeSpan const &right)
{
	return right * left;
}

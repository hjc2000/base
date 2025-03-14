#include "TimeSpan.h"

/**
 * @brief 构造函数
 *
 */
namespace base
{
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
} // namespace base

/**
 * @brief 转换
 *
 */
namespace base
{
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
} // namespace base

/**
 * @brief 四则运算
 *
 */
namespace base
{
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
} // namespace base

/**
 * @brief 比较
 *
 */
namespace base
{
	bool TimeSpan::operator==(base::TimeSpan const &another) const
	{
		return _span == another._span;
	}

	bool TimeSpan::operator<(base::TimeSpan const &another) const
	{
		return _span < another._span;
	}

	bool TimeSpan::operator>(base::TimeSpan const &another) const
	{
		return _span > another._span;
	}

	bool TimeSpan::operator<=(base::TimeSpan const &another) const
	{
		return _span <= another._span;
	}

	bool TimeSpan::operator>=(base::TimeSpan const &another) const
	{
		return _span >= another._span;
	}
} // namespace base

base::TimeSpan operator*(int64_t left, base::TimeSpan const &right)
{
	return right * left;
}

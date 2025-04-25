#include "TimeSpan.h"

/* #region 四则运算 */

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

base::TimeSpan base::TimeSpan::operator/(int64_t value) const
{
	return base::TimeSpan{std::chrono::nanoseconds{_span.count() / value}};
}

base::TimeSpan &base::TimeSpan::operator/=(int64_t value)
{
	_span = std::chrono::nanoseconds{_span.count() / value};
	return *this;
}

/* #endregion */

/* #region 比较 */

bool base::TimeSpan::operator==(base::TimeSpan const &another) const
{
	return _span == another._span;
}

bool base::TimeSpan::operator<(base::TimeSpan const &another) const
{
	return _span < another._span;
}

bool base::TimeSpan::operator>(base::TimeSpan const &another) const
{
	return _span > another._span;
}

bool base::TimeSpan::operator<=(base::TimeSpan const &another) const
{
	return _span <= another._span;
}

bool base::TimeSpan::operator>=(base::TimeSpan const &another) const
{
	return _span >= another._span;
}

/* #endregion */

base::TimeSpan operator*(int64_t left, base::TimeSpan const &right)
{
	return right * left;
}

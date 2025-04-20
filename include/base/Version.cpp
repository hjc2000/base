#include "Version.h"
#include "task/Mutex.h"

base::Version::Version(base::Version const &o)
{
	*this = o;
}

base::Version &base::Version::operator=(base::Version const &o)
{
	base::task::MutexGuard g[]{_lock, o._lock};
	_value = o._value;
	return *this;
}

base::Version &base::Version::operator++()
{
	base::task::MutexGuard g{_lock};
	++_value;
	return *this;
}

base::Version base::Version::operator++(int)
{
	base::task::MutexGuard g{_lock};
	base::Version ret{*this};
	++(*this);
	return ret;
}

/* #region 比较运算符 */

bool base::Version::operator==(base::Version const &another) const
{
	base::task::MutexGuard g[]{_lock, another._lock};
	return _value == another._value;
}

bool base::Version::operator<(base::Version const &another) const
{
	base::task::MutexGuard g[]{_lock, another._lock};
	return _value < another._value;
}

bool base::Version::operator>(base::Version const &another) const
{
	base::task::MutexGuard g[]{_lock, another._lock};
	return _value > another._value;
}

bool base::Version::operator<=(base::Version const &another) const
{
	base::task::MutexGuard g[]{_lock, another._lock};
	return _value <= another._value;
}

bool base::Version::operator>=(base::Version const &another) const
{
	base::task::MutexGuard g[]{_lock, another._lock};
	return _value >= another._value;
}

/* #endregion */

uint64_t base::Version::Value() const
{
	base::task::MutexGuard g{_lock};
	return _value;
}

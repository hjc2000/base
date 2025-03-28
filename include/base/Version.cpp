#include "Version.h"
#include "LockGuard.h"

base::Version::Version(base::Version const &o)
{
	*this = o;
}

base::Version &base::Version::operator=(base::Version const &o)
{
	base::LockGuard g{*_lock};
	base::LockGuard g1{*o._lock};
	_value = o._value;
	return *this;
}

base::Version &base::Version::operator++()
{
	base::LockGuard g{*_lock};
	++_value;
	return *this;
}

base::Version base::Version::operator++(int)
{
	base::LockGuard g{*_lock};
	base::Version ret{*this};
	++(*this);
	return ret;
}

/* #region 比较运算符 */

bool base::Version::operator==(base::Version const &another) const
{
	base::LockGuard g{*_lock};
	return _value == another._value;
}

bool base::Version::operator<(base::Version const &another) const
{
	base::LockGuard g{*_lock};
	return _value < another._value;
}

bool base::Version::operator>(base::Version const &another) const
{
	base::LockGuard g{*_lock};
	return _value > another._value;
}

bool base::Version::operator<=(base::Version const &another) const
{
	base::LockGuard g{*_lock};
	return _value <= another._value;
}

bool base::Version::operator>=(base::Version const &another) const
{
	base::LockGuard g{*_lock};
	return _value >= another._value;
}

/* #endregion */

uint64_t base::Version::Value() const
{
	base::LockGuard g{*_lock};
	return _value;
}
